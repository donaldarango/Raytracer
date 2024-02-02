#include "Ray.h"

class Ray {
public:
    Ray(glm::vec3 o, glm::vec3 d) {
        this->o = o;
        this->d = d;
    }

    glm::vec3 evaluate(float t) {
        // Ray Equation: p(t) = e + t(s − e).
        return o + (t*d);
    }
private:
    glm::vec3 o; // ray origin
    glm::vec3 d;  // ray direction
    
};