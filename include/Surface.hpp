#ifndef SURFACE_H
#define SURFACE_H

#include <glm/vec3.hpp>
#include "Ray.hpp"

class HitRecord;

class Surface {
public:
    glm::vec3 origin;

    Surface(glm::vec3 origin) : origin(origin) {}

    virtual HitRecord hit(Ray &ray, float t0, float t1) = 0;
};

#endif