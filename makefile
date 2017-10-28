ifeq ($(OS),Windows_NT)
#Windows
ext=.exe
LF=-lmingw32 -lSDL2main -lSDL2 -lglew32 -lOpenGL32 
LIB=-Llib
OPATH=obj/

else
#Linux (Probably)
ext=.out
LF=-lGL -lGLEW -lSDL2
OPATH=lobj/

endif



.PHONY: all clean
.SUFFIXES:

CC=g++
name=space

HEAD=display.h shader.h mesh.h
OBJ=main.o display.o shader.o mesh.o
INCLUDE=include

CF=-Wall

all: bin $(OPATH) $(patsubst %.o, $(OPATH)%.o, $(OBJ))
	$(CC) -o bin/$(name)$(ext) $(patsubst %.o, $(OPATH)%.o, $(OBJ)) $(LIB) $(LF)

bin:
	mkdir bin
	
$(OPATH):
	mkdir $(OPATH)
	
$(OPATH)%.o:%.cpp $(HEAD)
	$(CC) -c -o $@ $< $(CF) -I$(INCLUDE)

	