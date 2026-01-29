struct animatronicCommand {
	std::string type;
	double start;
};


struct positionCommand : public animatronicCommand {
	double end;
	int16_t bricklet;
	int16_t servo;
	int16_t pos;	
};

struct audiovideoCommand : public animatronicCommand {
	std::string id;
};

