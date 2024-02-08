#include "PointLight.hpp"
#include <algorithm>
#include <glm/glm.hpp>


class Surface;
class HitRecord;

PointLight::PointLight(float I, glm::vec3 p) : I(I), p(p) {}

glm::vec3 PointLight::illuminate(Ray &ray, HitRecord &hrec) {
    return glm::vec3(0,0,0);
}