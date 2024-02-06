#ifndef SURFACE_H
#define SURFACE_H

#include <glm/vec3.hpp>
#include "Ray.hpp"

class HitRecord;

class Surface {
public:
    glm::vec3 origin;
    glm::vec3 color;

    Surface(glm::vec3 origin, glm::vec3 color) : origin(origin), color(color) {}

    virtual HitRecord hit(Ray &ray, float t0, float t1) = 0;
};

#endif