#pragma once

class point{
  public:
    point(double ix = 0.0, double iy = 0.0, double iz = 0.0): x(ix), y(iy), z(iz){};
    double x;
    double y;
    double z;
    double distance(point o);
};

class sphere{
  public:
    sphere(point ip = point(), double ir = 0.0):p(ip), r(ir){};
    point p;
    double r;
};

class ray{
  public:
    ray(point ip = point(), point id = point()):p(ip), d(id){};
    point p;
    point d;
    double getnorm();
    void normalize();
};

bool sphere_collide(sphere s1,sphere s2);
bool ray_collide(ray r,sphere s);
