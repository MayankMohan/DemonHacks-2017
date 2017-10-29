#include <cstdio>
#include <GL/glew.h>
#include "display.h"

Display::Display(size_t width, size_t height, const char* title, Uint32 framecap){
		
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if(_window == NULL){
		printf("ERROR: Window initialization fail: %s \n", SDL_GetError());
	}
	_context = SDL_GL_CreateContext(_window);
	
	GLenum status = glewInit();
	
	if(status != GLEW_OK){
		printf("ERROR: glew initialization fail: %s \n", glewGetErrorString(status));
	}
	
	_opt = 0;
	_frameCap = framecap;
	_minDelay = 1000 / _frameCap;
	printf("fCap: %u\nDelay: %ums\n", _frameCap, _minDelay);
	_lastTick = SDL_GetTicks();
	_running = true;
}

Display::~Display(){
	SDL_GL_DeleteContext(_context);
	SDL_DestroyWindow(_window);
}

bool Display::FrameReady(){
	Uint32 curtime = SDL_GetTicks();
	if(Opt_Chk(DISP_FPS_UNCAP)){
		//printf("%u\n", (curtime - _lastTick));
		_lastTick = curtime;
		return true;
	}
	if(SDL_TICKS_PASSED(curtime, _lastTick + _minDelay)){
		//printf("%u\n", (curtime - _lastTick));
		_lastTick = curtime;
		return true;
	}
	return false;
}

void Display::Clear(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update(){
	SDL_GL_SwapWindow(_window);
	SDL_Event e;
	
	while(SDL_PollEvent(&e)){
		if(e.type == SDL_QUIT){
			_running = false;
		}
	}
}
