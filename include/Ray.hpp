#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>
#include "Surface.hpp"
#include "HitRecord.hpp"

class Surface;
class HitRecord;

class Ray {
public:

    Ray(glm::vec3 o, glm::vec3 d);
    glm::vec3 evaluate(float t);
    bool inShadow(Surface** objects, int numObjects);

    glm::vec3 getOrigin();
    glm::vec3 getDirection();

private:

    glm::vec3 o; // ray origin
    glm::vec3 d;  // ray direction

};

#endif