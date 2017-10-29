# include <cmath>
# include <cstdio>
# include <entities.h>



//triggers when collsion occurs which is not used here????
Player::Player(){
  lives = 3;
  score = 0;
}

void Player::damage(){
Player lives-=1
  
}

void Enemy::damage(){
Enemy hp-=1
}
bool Enemy::alive(){
if (hp<=0){
  return false;
}
return true;
}

bool player_die(Player lives){

return false;
};