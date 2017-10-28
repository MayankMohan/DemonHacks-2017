#include <cstdio>
#include <cstring>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"

int main(int argc, char **argv){
	//Attribute setup
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	Display d(480, 640, "Window");
	
	float test = 1.0;
	
	if(argc > 1){
		for(int i = 0; i < argc; i++){
			printf("%s\n", argv[i]);
			if(strcmp(argv[i], "-uncap") == 0){
				printf("Uncapping Framerate\n");
				d.Opt_Set(Display::DISP_FPS_UNCAP);
			}
		}
	}
	
	
	Vertex vertices[] = {	Vertex(glm::vec3(-1, -1, 0)),
							Vertex(glm::vec3(0, 1, 0)),
							Vertex(glm::vec3(1, -1, 0))
	};
	
	
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));
	
	Shader shad("./resource/shad");
	
	while(d.Running()){
		d.Clear(test);
		if(d.FrameReady()){
			test -= 0.01;
			shad.Bind();
			mesh.Draw();
			d.Update();
		}
	}
	
	d.~Display();
	SDL_Quit();
	printf("Press any key to continue...");
	getchar();
	return 0;
}
