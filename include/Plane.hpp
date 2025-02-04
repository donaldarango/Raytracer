#ifndef PLANE_H
#define PLANE_H

#include "Surface.hpp"

class HitRecord;
class Material;

class Plane : public Surface {
public:

    Plane(glm::vec3 origin, Material &material, glm::vec3 normal);

    HitRecord hit(Ray &ray, float t0, float t1) override; // returns t value 

    glm::vec3 normal;

};

#endif