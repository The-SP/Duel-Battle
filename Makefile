LIBRARIES = -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio
INCLUDES = -I src/include -I headers
# CFLAGS = -Wall -Werror

# OBJS = main.o menu.o bat.o ball.o Shooter.o bullet.o plane.o asteroid.o
# CPP_FILES = main.cpp headers/menu.cpp headers/bat.cpp headers/ball.cpp headers/Shooter.cpp headers/bullet.cpp headers/plane.cpp headers/asteroid.cpp

OBJS = *.o
CPP_FILES = main.cpp headers/*.cpp

all: compile link

compile:
	g++ -c $(CPP_FILES) $(CFLAGS) $(INCLUDES)

link:
	g++ $(OBJS) -o main -L src/lib $(LIBRARIES)
	rm *.o
	main