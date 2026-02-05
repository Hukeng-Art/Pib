#include "AudioVideoControl.h"

// constructor mostly copypasted from SDL_Application
// window can not be closed manually, is only closed upon Robot class deletion
AudioVideoControl::AudioVideoControl() {
	
	if (!SDL_Init(SDL_FLAGS_AUDIOVIDEO)) { // Initialize SDL module
		throw std::runtime_error("Error initiating SDL for AudioVideo.\n");
	}
	
	
	if (!TTF_Init()) { // initialize TTF module
		throw std::runtime_error("Error initiating TTF for AudioVideo.\n");
	}
	
	
	if (!MIX_Init()) { // initialize Mixer module (audio)
		throw std::runtime_error("Error initiating MIX for AudioVideo.\n");
	}
	
		
	// create window pointer
	window = SDL_CreateWindow(AUDIOVIDEO_WIN_TITLE, AUDIOVIDEO_WIN_WIDTH, AUDIOVIDEO_WIN_HEIGHT, 0);
	
	if (!window) { // check if window pointer is populated
		throw std::runtime_error("Error creating window.\n");
	}
	
	// set window to resizable
	SDL_SetWindowResizable(window, true);
	
	// SDL_CreateRenderer() returns pointer to renderer for window
	renderer = SDL_CreateRenderer(window, NULL);
	
	// check if renderer pointer is populated 
	if (!renderer) {
		throw std::runtime_error("Error creating Renderer.\n");
	}
	
	
	// create audiospec struct to initialize mixer
	SDL_AudioSpec audiospec;
	audiospec.format = MIX_DEFAULT_FORMAT;
	audiospec.channels = MIX_DEFAULT_CHANNELS; // stereo or mono
	audiospec.freq = MIX_DEFAULT_FREQUENCY;
	
	// populate mixer and default tracks
	mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audiospec);
	sfx_track = MIX_CreateTrack(mixer);
	music_track = MIX_CreateTrack(mixer);
	
	// call update() once to open window
	update(0);
}


AudioVideoControl::~AudioVideoControl() {
	
	free_audios();
	free_images();
	
	if (renderer) { // if pointer to renderer is available
		SDL_DestroyRenderer(renderer); // free memory at renderer pointer
		renderer = NULL;               // set dangling pointer to null
	}
	
	if (window) { // if pointer to window is available
		SDL_DestroyWindow(window); // free memory at window pointer
		window = NULL;             // set dangling pointer to null
	}
	
	if (mixer) { // if pointer to mixer is available
		MIX_DestroyMixer(mixer); // free memory at mixer pointer
		mixer = NULL;            // set dangling pointer to null
	}
	
	MIX_Quit();         // take mixer module offline
	TTF_Quit();         // take ttf module offline
	SDL_Quit();         // take module offline after unallocating memory

}


void AudioVideoControl::play_sfx(std::string id) {
	
	if (audios.find(id) == audios.end()) {
		fprintf(stderr, "Error - id \"%s\" does not match any loaded track.\n", id.data());
		return;
	}
	
	if (!MIX_SetTrackAudio(sfx_track, audios[id])) {
		fprintf(stderr, "Error setting music track: %s\n", SDL_GetError());
	}
	if (!MIX_PlayTrack(sfx_track, 0)) {
		fprintf(stderr, "Error playing music: %s\n", SDL_GetError());
	}

}


void AudioVideoControl::play_music(std::string id) {
	
	if (audios.find(id) == audios.end()) {
		fprintf(stderr, "Error - id \"%s\" does not match any loaded track.\n", id.data());
		return;
	}
	
	if (!MIX_SetTrackAudio(music_track, audios[id])) {
		fprintf(stderr, "Error setting music track: %s\n", SDL_GetError());
	}
	if (!MIX_PlayTrack(music_track, 0)) {
		fprintf(stderr, "Error playing music: %s\n", SDL_GetError());
	}
}


void AudioVideoControl::push_audio(std::string id, std::string path) {
	
	MIX_Audio *audio = MIX_LoadAudio(mixer, path.c_str(), true);
	audios[id] = audio;

}


void AudioVideoControl::free_audio(std::string id) {
	if (audios.find(id) == audios.end()) {
		fprintf(stderr, "Error deleting audio - id \"%s\" does not match any loaded audio.\n", id.data());
		return;
	}
	
	MIX_DestroyAudio(audios[id]);
	audios.erase(id);
}


void AudioVideoControl::free_audios() {
	for (auto audio : audios) {
		free_audio(audio.first);
	}
}


void AudioVideoControl::set_image(std::string id) {
	if (images.find(id) == images.end()) {
		fprintf(stderr, "Error setting image - id \"%s\" does not match any loaded image.\n", id.data());
		return;
	}
	
	current_image = images[id];
}


void AudioVideoControl::push_image(std::string id, std::string path) {
	images[id] = IMG_LoadTexture(renderer, path.c_str());
}


void AudioVideoControl::free_image(std::string id) {
	if (images.find(id) == images.end()) {
		fprintf(stderr, "Error deleting image - id \"%s\" does not match any loaded image.\n", id.data());
		return;
	}
	
	SDL_DestroyTexture(images[id]);
	images.erase(id);
}


void AudioVideoControl::free_images() {
	for (auto image : images) {
		free_image(image.first);
	}
}

	
void AudioVideoControl::draw_image() {
	SDL_RenderTexture(renderer, current_image, NULL, NULL);
}

void AudioVideoControl::update(double delta) {
	
	SDL_RenderClear(renderer);
	
	if (current_image) {
		draw_image();
	}
	
	SDL_RenderPresent(renderer);
}
