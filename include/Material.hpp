#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

class Material {

public:

    Material(glm::vec3 color, float k_a);

    glm::vec3 evaluateColor(glm::vec3 l, glm::vec3 v, glm::vec3 n);

    glm::vec3 color;
    float k_a; // ambient coefficient

};


#endif