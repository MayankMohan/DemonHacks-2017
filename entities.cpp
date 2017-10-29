# include <cmath>
# include <cstdio>
# include "entities.h"



//triggers when collsion occurs which is not used here????
Player::Player(){
  lives = 3;
  score = 0;
  
}
Enemy::Enemy(){
  hp=5;
  //this one could be removed
  spawn_count=25;


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

bool Player::alive(){
if (lives<=0){
return false;
}
return true;
};