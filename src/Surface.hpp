#ifndef SURFACE_H
#define SURFACE_H

#include <glm/vec3.hpp>
#include "Ray.hpp"
#include "HitRecord.cpp"

class Surface {
public:
    glm::vec3 origin;

    Surface() {
        this->origin = glm::vec3(0,0,0);
    }
    Surface(glm::vec3 origin) {
        this->origin = origin;
    }

    HitRecord hit(Ray ray, float t0, float t1);
};

#endif