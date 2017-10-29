#include <cstdio>
#include <string>
#include <cstring>
#include <vector>

#include <GL/glew.h>

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "modelParser.h"
#include "entities.h"
#include "collision.h"


#define W_HEIGHT 1080
#define W_WIDTH 1920

double fRand(double fMin, double fMax);

int main(int argc, char **argv){
	//Attribute setup
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	Display d(W_WIDTH, W_HEIGHT, "Star Box");
	
	std::string path(argv[0]);
	path = path.substr(0,path.find_last_of('/'));
	float test = 1.0;

	for(int i = 0; i < argc; i++){
		printf("%s\n", argv[i]);
		if(strcmp(argv[i], "-uncap") == 0){
			printf("Uncapping Framerate\n");
			d.Opt_Set(Display::DISP_FPS_UNCAP);
		}
	}
	
	/*
	SDL_GameController *controller = NULL;
	printf("%d", SDL_NumJoysticks());
	for (int i = 0; i < SDL_NumJoysticks(); ++i) 
		if (SDL_IsGameController(i)) {
			if (controller) {
				break;
			} else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}*/
	getchar();
	
	int num_objs = 3;
	std::string objs[] = {
		"f1ship.obj",
		"wasp.obj",
		"meteoroid.obj"
	};
	Transform* trans = new Transform();
	//Mesh* meshes[num_objs];
	Vertex** vertices = (Vertex**)malloc(sizeof(Vertex*) * num_objs);
	int sizes[num_objs];
	for(int i = 0; i < num_objs; i++){
		Vertex* temp;
		sizes[i] = parseOBJ((path + "/../resource/" + objs[i]).c_str(), &temp);
		printf("%d\n", sizes[i]);
		if(sizes[i] == 0){
			printf("Unable to parse OBJ file\nPress any key to continue...");
			getchar();
			return 1;
		}
		vertices[i] = temp;
	}
	
	Shader shad((path + "/../resource/shad").c_str());
	Camera cam(glm::vec3(0,0,8), 70.0f, (float)W_WIDTH / (float)W_HEIGHT, 0.01f, 800.0f);
	
	Mesh* playermesh = new Mesh(trans, vertices[0], sizes[0]);
	Player player(playermesh);
	
	std::vector<Enemy> enemies;
	
	srand(time(NULL));
	
	double xSpd, ySpd;
	while(d.Running()){
		if(rand() % 25 == 0){
			double spawnX = fRand(-5, 5);
			double spawnY = fRand(-3.25, 3.25);
			Transform* tempTrans = new Transform(glm::vec3(spawnX, spawnY, -100), glm::vec3(), glm::vec3());
			Mesh* enemymesh = new Mesh(tempTrans, vertices[1], sizes[1]);
			Enemy tempEnem(enemymesh);
			enemies.push_back(tempEnem);
		}
		d.Clear(test);
		for(size_t i = 0; i < enemies.size(); i++){
			enemies[i].getTrans()->getPos().z += 0.5;
			if(enemies[i].getTrans()->getScale().x < 1.0){
				double val = enemies[i].getTrans()->getScale().x;
				val += 0.01;
				if(1.0 < val){
					val = 1.0;
				}
				enemies[i].getTrans()->getScale().x = val;
				enemies[i].getTrans()->getScale().y = val;
				enemies[i].getTrans()->getScale().z = val;
			}
			if(enemies[i].getTrans()->getPos().z > 5.0){
				delete enemies[i].getTrans();
				enemies.erase(enemies.begin() + i);
				player.damage();
			}
		}
		if(d.FrameReady()){
			shad.Bind();
			const Uint8* state = SDL_GetKeyboardState(NULL);
				if(state[SDL_SCANCODE_LEFT] && !state[SDL_SCANCODE_RIGHT]){
					xSpd -= 0.1;
					if(xSpd < -0.5)
						xSpd = -0.5;
				}else if(!state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_RIGHT]){
					xSpd += 0.1;
					if(xSpd > 0.5)
						xSpd = 0.5;
				}else{
					xSpd /= 1.1;
				}
			
				if(state[SDL_SCANCODE_DOWN] && !state[SDL_SCANCODE_UP]){
					ySpd -= 0.1;
					if(ySpd < -0.5)
						ySpd = -0.5;
				}else if(!state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_UP]){
					ySpd += 0.1;
					if(ySpd > 0.5)
						ySpd = 0.5;
				}else{
					ySpd /= 1.1;
				}
				
				double curx, cury;
				curx = player.getTrans()->getPos().x;
				if(curx + xSpd < 5 && curx + xSpd > -5)
					player.getTrans()->getPos().x += xSpd;
				player.getTrans()->getRot().z = -xSpd*1.2;
				cury = player.getTrans()->getPos().y;
					if(cury + ySpd < 3.25 && cury + ySpd > -3.25)
						player.getTrans()->getPos().y += ySpd;
				player.getTrans()->getRot().x= ySpd/1.3;
			//for(int i = 0; i < num_objs; i++){
			//	shad.Update(meshes[i]->getTrans(), cam);
			//	meshes[i]->Draw();
			//}
			
			shad.Update(player.getTrans(),cam);
			player.draw();
			for(size_t i = 0; i < enemies.size(); i++){
				shad.Update(enemies[i].getTrans(),cam);
				enemies[i].draw();
			}
			
			d.Update();
		}
	}
	
	d.~Display();
	SDL_Quit();
	return 0;
}

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
