#ifndef HITRECORD_H
#define HITRECORD_H

#include <glm/vec3.hpp>

class Surface;

class HitRecord {
public:

    HitRecord();
    HitRecord(Surface* s, float t, glm::vec3 n);

    Surface* s;
    float t;
    glm::vec3 n; // normal
};

#endif