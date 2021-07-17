LIBRARIES = -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio
INCLUDES = -I src/include -I headers
COMPILER_FLAGS = -Wall -Werror

OBJS = *.o
CPP_FILES = main.cpp headers/*.cpp

all: compile link

compile:
	g++ -c $(CPP_FILES) $(COMPILER_FLAGS) $(INCLUDES)

link:
	g++ $(OBJS) -o main -L src/lib $(LIBRARIES)
	main

clean:
	del *.o 
	del *.exe