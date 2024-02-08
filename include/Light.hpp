#ifndef LIGHT_H
#define LIGHT_H

#include "Ray.hpp"
#include "HitRecord.hpp"

class Light {

public:

    glm::vec3 illuminate(Ray& ray, HitRecord& hrec);

};


#endif