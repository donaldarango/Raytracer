#include "Material.hpp"
#include <algorithm>
#include <iostream>

Material::Material(glm::vec3 color, float k_a, float k_d, float k_s) {
    this->color = color;
    this->k_a = k_a;
    this->k_d = k_d;
    this->k_s = k_s;
}

glm::vec3 Material::evaluateColor(glm::vec3 l, glm::vec3 v, glm::vec3 n) {

    float L_a = k_a;
    float L_d = k_d * std::max(0.0f,glm::dot(l,n));
    float L_s = 0;

    float L = L_a + L_d + L_s;
    std::cout << "L: " << L <<  std::endl;
    std::cout << "L_d: " << L_d <<  std::endl;
    std::cout << "k_d: " << k_d <<  std::endl;

    // return glm::clamp(color + L, 0.0f, 255.0f);
    return color * L;
}