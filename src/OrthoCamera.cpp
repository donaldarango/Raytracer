#include "../include/OrthoCamera.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/perpendicular.hpp>


    OrthoCamera::OrthoCamera(glm::vec3 viewPoint, glm::vec3 viewDir, glm::vec3 upward, float width, float height) 
        : Camera(viewPoint, viewDir, upward, width, height) 
    {
        this->w = -(viewDir);
        this->u = glm::perp(w, upward);
        this->v = glm::perp(u,w);
    }

    glm::vec3 OrthoCamera::GenerateRayOrigin(float u, float v) {
        return viewPoint + (u * this->u) + (v * this->v);
    }
