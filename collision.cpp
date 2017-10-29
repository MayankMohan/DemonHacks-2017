#include <cmath>
#include <cstdio>

#include "collision.h"
//needs to be written in C++
//in the update function print the coordinates of the X, Y, Z 

double point::distance(point o){
  return sqrt(pow(x - o.x, 2)+pow(y - o.y, 2)+pow(z - o.z, 2));
}

double ray::getnorm(){
  return sqrt(pow(d.x, 2)+pow(d.y, 2)+pow(d.z, 2));
}

void ray::normalize(){
  double divisor = getnorm();
  d.x /= divisor;
  d.y /= divisor;
  d.z /= divisor;
}

bool sphere_collide(sphere s1,sphere s2) {
  double space = s1.r + s2.r;

  //the important part
  double distance= sqrt(pow(s1.p.x-s2.p.x, 2)+pow(s1.p.y-s2.p.y, 2)+pow(s1.p.z-s2.p.z, 2));

  if (distance < space) {

    printf("COLLIDED\n");
      return true;
    };
  return false;
};

/*
//we have to cycle through all the objects to check for collisions
for i=0;sphere1=num_of_objects;i++{
for c==0;sphere2==num_of_objects;c++{
sphere_collide(sphere1,sphere2)
}
}
*/

bool ray_collide(ray r, sphere s) {

r.normalize();

// The dot funciton can replace the math?

ray v1(r.p,point(s.p.x-r.p.x, s.p.y-r.p.y, s.p.z - r.p.z));
double theta = acos(r.d.x * v1.d.x + r.d.y * v1.d.y + r.d.z * v1.d.z);
double m = cos(theta) * v1.getnorm();

point close(r.p.x + r.d.x*m, r.p.y + r.d.y*m, r.p.z + r.d.z*m );


if (close.distance(s.p) < s.r){

  printf("Oogabooga!!\n");
  return true;
}


return false;
};







