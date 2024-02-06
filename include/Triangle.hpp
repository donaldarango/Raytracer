#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Surface.hpp"

class HitRecord;

class Triangle : public Surface {
public:
    Triangle(glm::vec3 origin, glm::vec3 color, glm::vec3 a, glm::vec3 b, glm::vec3 c);

    HitRecord hit(Ray &ray, float t0, float t1) override; // returns t value 

    // Triangle vertices
    glm::vec3 a;
    glm::vec3 b;
    glm::vec3 c;

};

#endif