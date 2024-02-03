#include "Ray.h"


Ray::Ray(glm::vec3 o, glm::vec3 d) {
        this->o = o;
        this->d = d;
    }

glm::vec3 Ray::evaluate(float t) {
    // Ray Equation: p(t) = e + t(s − e).
    return o + (t*d);
}
    