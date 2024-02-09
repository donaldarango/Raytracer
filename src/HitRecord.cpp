#include "../include/HitRecord.hpp"
#include "../include/Surface.hpp"

HitRecord::HitRecord(Surface* s, float t, glm::vec3 n) {
    this->s = s;
    this->t = t;
    this->n = n;
}

HitRecord::HitRecord(){
    this->s = nullptr;
    this->t = INFINITY;
    this->n = glm::vec3(0,0,0);
}