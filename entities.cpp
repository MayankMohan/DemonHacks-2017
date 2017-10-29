# include <cmath>
# include <cstdio>
# include "entities.h"

void Entity::draw(){
	mesh->Draw();
}

//triggers when collsion occurs which is not used here????
Player::Player(Mesh* m){
	mesh = m;
	lives = 3;
	score = 0;
  
}

Enemy::Enemy(Mesh* m){
	mesh = m;
	hp=5;
}
void Player::addScore(int i){
score+=i;
}

void Player::damage(){
lives-=1;
}

void Enemy::damage(){
hp-=1;
}

bool Enemy::alive(){
if (hp<=0){
  return false;
}
return true;
};
