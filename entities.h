#pragma once

#include <glm/glm.hpp>


class Entity{
	protected:
		glm::vec3 position;
		glm::vec3 direction;
		double size;
    double min_size;
    double max_size;
	public:
    bool hit();
};

class Player:public Entity{
	private:
		int lives;
		int score;
  public:
    Player();
    void addScore(int i);
    void damage();
    bool alive();
};

class Enemy: public Entity{
  private:
    int hp;
    int spawn_count;
  public:
    Enemy();
    void damage();
    bool alive();
};
	//assert certain positions to other entities; think using random

