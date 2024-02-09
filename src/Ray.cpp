#include "../include/Ray.hpp"

Ray::Ray(glm::vec3 o, glm::vec3 d) {
    this->o = o;
    this->d = d;
}

glm::vec3 Ray::evaluate(float t) {
    return o + (t * d);
}

bool Ray::inShadow(Surface** objects, int numObjects) {
    for (int i = 0; i < numObjects; ++i) {
                HitRecord hitRecord = objects[i]->hit(*this, 0, INFINITY);
                if (hitRecord.t != INFINITY){
                     return true;
                }
            }
    return false;

}

glm::vec3 Ray::getOrigin() {
    return o;
}

glm::vec3 Ray::getDirection() {
    return d;
}
