#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include <glm/glm.hpp>
#include "Ray.hpp"
#include "HitRecord.hpp"

class Ray;
class HitRecord;

class DirectionalLight {

public:

    DirectionalLight(float I, glm::vec3 direction);

    glm::vec3 illuminate(Ray &ray, HitRecord &hrec);

    float I; // 
    glm::vec3 direction;

};



#endif