#ifndef AUDIOVIDEO_CONTROL_H
#define AUDIOVIDEO_CONTROL_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <map>

#define SDL_FLAGS_AUDIOVIDEO (SDL_INIT_VIDEO | SDL_INIT_AUDIO)

#define AUDIOVIDEO_WIN_TITLE "pib_eyes"
#define AUDIOVIDEO_WIN_HEIGHT 500
#define AUDIOVIDEO_WIN_WIDTH 800

#define MIX_DEFAULT_FREQUENCY 44100
#define MIX_DEFAULT_FORMAT SDL_AUDIO_S16
#define MIX_DEFAULT_CHANNELS 2


class AudioVideoControl {
	
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	MIX_Mixer *mixer;
	MIX_Track *sfx_track;
	MIX_Track *music_track;
	
	std::map<std::string, MIX_Audio*> audios;
	std::map<std::string, SDL_Texture*> images;
	
	SDL_Texture* current_image;
	
	public:
	AudioVideoControl();
	~AudioVideoControl();
	
	void play_sfx(std::string id);
	void play_music(std::string id);
	
	void push_audio(std::string id, std::string path);
	void free_audio(std::string id);
	void free_audios();
	
	void set_image(std::string id);
	void push_image(std::string id, std::string path);
	void free_image(std::string id);
	void free_images();

	void draw_image();
	void update(double delta);
	
		
};

#endif
