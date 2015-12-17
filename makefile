LDFLAGS = -lGL -lGLU -lglut
CFLAGS=-g -Wall -std=c++11
CC=gcc
EXEEXT=
RM=rm

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
        EXEEXT=.exe #on windows applications must have .exe extension
        RM=del #rm command for windows powershell
    LDFLAGS = -lfreeglut -lglu32 -lopengl32
else
        # OS X
        OS := $(shell uname)
        EXEEXT=.x
        ifeq ($(OS), Darwin)
                LDFLAGS = -lstdc++ -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated-declarations
        endif
endif

all: pacman

pacman: main.cpp
        $(CC) -o pacman.x main.cpp $(LDFLAGS)

clean:
        $(RM) *.x
