#include <cstdio>
#include <cstring>

#include <GL/glew.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "modelParser.h"


#define W_HEIGHT 1080
#define W_WIDTH 1920

int main(int argc, char **argv){
	//Attribute setup
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	Display d(W_WIDTH, W_HEIGHT, "Window");
	
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
	
	SDL_GameController *joy = SDL_GameControllerOpen(0);
	if(joy == NULL){
		printf("Error\n");
	}
	
	/*
	SDL_GameController *controller = NULL;
	printf("%d", SDL_NumJoysticks());
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			if (controller) {
				break;
			} else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}*/
	getchar();
	
	
	Vertex* vertices;
	int numverts = parseOBJ("../resource/f1ship.obj", &vertices);
	printf("numvert: %d", numverts);
	if(numverts == 0){
		printf("Unable to parse OBJ file\nPress any key to continue...");
		getchar();
		return 1;
	}
	
	
	Mesh mesh(vertices, numverts);
	Shader shad("../resource/shad");
	Transform trans;
	Camera cam(glm::vec3(0,1,-4), 70.0f, (float)W_WIDTH / (float)W_HEIGHT, 0.01f, 800.0f);
	
	while(d.Running()){
		d.Clear(test);
		if(d.FrameReady()){
			trans.getPos().x = sinf(test);
			trans.getRot().z = sinf(test);
			test -= 0.01;
			shad.Bind();
			shad.Update(trans, cam);
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
