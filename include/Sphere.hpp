#ifndef SPHERE_H
#define SPHERE_H

#include "Surface.hpp"

class HitRecord;

class Sphere : public Surface {
public:
    Sphere(glm::vec3 origin, glm::vec3 color, float radius);

    HitRecord hit(Ray &ray, float t0, float t1) override; // returns t value 
    float radius;

};

#endif