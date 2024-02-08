#include "Material.hpp"

Material::Material(glm::vec3 color, float k_a) : color(color), k_a(k_a) {}

glm::vec3 Material::evaluateColor(glm::vec3 l, glm::vec3 v, glm::vec3 n) {
    
}