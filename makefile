ifeq ($(OS),Windows_NT)
#Windows
ext=.exe
LF=-lmingw32 -lSDL2main -lSDL2 -lglew32 -lOpenGL32 
LIB=-Llib
OPATH=obj
RM=del /f
RMDIR=rd /s /q
MD=md

else
#Linux (Probably)
ext=.out
LF=-lGL -lGLEW -lSDL2
OPATH=lobj
RM=rm
RMDIR=rm -rf
MD=mkdir

endif



.PHONY: all clean
.SUFFIXES:

CC=g++
name=space

HEAD=display.h shader.h mesh.h modelParser.h
OBJ=main.o display.o shader.o mesh.o modelParser.o
INCLUDE=include

CF=-Wall -g

################             Recipes                ###############################

all: bin $(OPATH) $(patsubst %.o, $(OPATH)/%.o, $(OBJ))
	$(CC) -o bin/$(name)$(ext) $(patsubst %.o, $(OPATH)/%.o, $(OBJ)) $(LIB) $(CF) $(LF)

bin:
	$(MD) bin
	
$(OPATH):
	$(MD) $(OPATH)
	
$(OPATH)/%.o:%.cpp $(HEAD)
	$(CC) -c -o $@ $< $(CF) -I$(INCLUDE)
	
clean:
	$(RMDIR) bin
	$(RMDIR) $(OPATH)

	