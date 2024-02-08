#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Surface.hpp"

class HitRecord;
class Material;

class Triangle : public Surface {
public:
    Triangle(glm::vec3 origin, Material &material, glm::vec3 vertexA, glm::vec3 vertexB, glm::vec3 vertexC);

    HitRecord hit(Ray &ray, float t0, float t1) override; // returns t value 

    // Triangle vertices
    glm::vec3 vertexA;
    glm::vec3 vertexB;
    glm::vec3 vertexC;

};

#endif