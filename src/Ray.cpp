#include "Ray.hpp"


Ray::Ray(glm::vec3 o, glm::vec3 d) {
        this->o = o;
        this->d = d;
    }

glm::vec3 Ray::evaluate(float t) {
    return o + (t*d);
}

glm::vec3 Ray::getOrigin() {
    return o;
}

glm::vec3 Ray::getDirection() {
    return d;
}
    