#ifndef ORTHOCAMERA_H
#define ORTHOCAMERA_H

#include "Camera.hpp"
#include <glm/vec3.hpp>

class OrthoCamera : public Camera {
    public:
        OrthoCamera(glm::vec3 viewPoint, glm::vec3 viewDir, glm::vec3 upward, float width, float height);
        glm::vec3 GenerateRayOrigin(float u, float v);

};

#endif