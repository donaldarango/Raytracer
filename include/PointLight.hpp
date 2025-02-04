#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.hpp"

class PointLight : public Light{

public:

    PointLight(float I, glm::vec3 p);

    glm::vec3 illuminate(Ray &ray, HitRecord &hrec);

    float I; // Intensity
    glm::vec3 p; // position
    
};

#endif