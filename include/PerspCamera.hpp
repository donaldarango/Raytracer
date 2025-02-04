#ifndef PERSPCAMERA_H
#define PERSPCAMERA_H

#include "Camera.hpp"
#include <glm/vec3.hpp>

class PerspCamera : public Camera {
    public:
        PerspCamera(glm::vec3 viewPoint, glm::vec3 viewDir, glm::vec3 upward, float width, float height, float d);

        glm::vec3 GenerateRayOrigin(float u, float v);
        glm::vec3 GenerateRayDirection(float u, float v);

        float d;
        
};

#endif