#We have a cpp file named project_name.cpp
OBJS = main.cpp
MODULES = Tetromino.cpp Grid.cpp Specifications.cpp Game.cpp 
OBJ_NAME = main
CC = g++
INCLUDE_PATHS = -IC:\mingw_dev_lib\x86_64-w64-mingw32\include\SDL2
LIBRARY_PATHS = -LC:\mingw_dev_lib\x86_64-w64-mingw32\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
#This is the target that compiles our executable
all : $(OBJS) 
	$(CC) $(OBJS) $(MODULES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)