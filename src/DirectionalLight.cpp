#include "DirectionalLight.hpp"
#include "Surface.hpp"
#include <algorithm>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <iostream>

class Surface;
class Material;

DirectionalLight::DirectionalLight(float I, glm::vec3 direction) : I(I), direction(glm::normalize(direction)) {}

glm::vec3 DirectionalLight::illuminate(Ray &ray, HitRecord &hrec) {

    glm::vec3 x = ray.evaluate(hrec.t);
    glm::vec3 l = direction;
    glm::vec3 n = hrec.n;
    glm::vec3 v = -ray.getDirection();

    // E = Hcosθ
    glm::vec3 color = hrec.s->material.evaluateColor(l,v,n);
    std::cout<< "evaluate: "<<glm::to_string(color) << std::endl;
    return color;

}


