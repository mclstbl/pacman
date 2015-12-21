LDFLAGS = -lGL -lGLU -lglut
CFLAGS=-g -w -std=c++11
CC=g++
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
	  CFLAGS =
		LDFLAGS = -w -std=c++11 -framework Carbon -framework OpenGL -framework GLUT -Wno-deprecated-declarations 
	endif
endif

all: pacman

pacman: 
	$(CC) $(CFLAGS) -o pacman$(EXEEXT) main.cpp pacman.cpp ghost.cpp food.cpp text.cpp $(LDFLAGS)

test:
	$(CC) $(CFLAGS) -o test$(EXEEXT) mainold.cpp pacman.cpp ghost.cpp food.cpp text.cpp $(LDFLAGS)
clean:
	$(RM) *$(EXEEXT)
