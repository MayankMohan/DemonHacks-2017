#pragma once

#include <glm/glm.hpp>

#include "transform.h"
#include "mesh.h"

class Entity{
	protected:
		Mesh* mesh;
		
	public:
		Entity(){};
		Transform* getTrans(){return mesh->getTrans();};
		bool hit();
		void draw();
		virtual void damage() = 0;
};

class Player:public Entity{
	private:
		int lives;
		int score;
	public:
		Player(Mesh* m);
		void addScore(int i);
		void damage();
};

class Enemy: public Entity{
	private:
		int hp;
	public:
		Enemy(Mesh* m);
		void damage();
		bool alive();
};
	//assert certain positions to other entities; think using random

