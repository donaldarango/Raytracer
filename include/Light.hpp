#ifndef LIGHT_H
#define LIGHT_H

#include "Ray.hpp"
#include "HitRecord.hpp"

class HitRecord;
class Ray;

class Light {

public:

    virtual glm::vec3 illuminate(Ray& ray, HitRecord& hrec) = 0;

};


#endif