#pragma once

#include "SDL2/SDL.h"

class Display{
	public:
		Display(size_t width, size_t height, const char* title, Uint32 framecap = 60);
		~Display();
		
		const bool Running(){return _running;};
		bool FrameReady();
		void Update();
		void Clear(float r = 1.0, float g = 0.65, float b = 0.60, float a = 1.0);
		
		void Opt_Set(int opt){_opt = opt;};
		const int Opt_Get(){return _opt;};
		const bool Opt_Chk(int chk){return (_opt & chk) == chk;};
		
		enum DISP_OPT {
			DISP_FPS_UNCAP = 0b0001
		};
	private:
		SDL_Window* _window;
		SDL_GLContext _context;
		bool _running;
		
		Uint32 _frameCap;
		Uint32 _lastTick;
		Uint32 _minDelay;
		
		//BITMASK FLAGS
		int _opt;
};
