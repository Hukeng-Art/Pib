g++  main_animatronic.cpp  -o main_animatronic.o \
	-g --debug \
	-I../Pib_Tinkerforge/Resources/ \
	-I../Pib_Tinkerforge/Classes \
	-I../Pib_Tinkerforge/Structs \
	-L/usr/local/lib \
	../Pib_Tinkerforge/Resources/brick_hat.c \
	../Pib_Tinkerforge/Resources/bricklet_servo_v2.c \
	../Pib_Tinkerforge/Resources/ip_connection.c \
	../Pib_Tinkerforge/Resources/bricklet_solid_state_relay_v2.c \
	-lSDL3 -lSDL3_image -lSDL3_ttf -lSDL3_mixer
