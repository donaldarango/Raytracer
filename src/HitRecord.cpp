#include "Surface.hpp"
#include <glm/vec3.hpp>

class HitRecord {
public:

    HitRecord(Surface s, float t, glm::vec3 n) {
        this->s = s;
        this->t = t;
        this->n = n;
    }

    Surface s;
    float t;
    glm::vec3 n; // normal
};