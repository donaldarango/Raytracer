#include "PerspCamera.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


    PerspCamera::PerspCamera(glm::vec3 viewPoint, glm::vec3 viewDir, glm::vec3 upward, float width, float height, float d) 
        : Camera(viewPoint, viewDir, upward, width, height), d(d)
    {
        this->w = -(glm::normalize(viewDir));
        this->u = glm::normalize(glm::cross(upward, viewDir));
        this->v = glm::normalize(glm::cross(viewDir,u));

    }

    glm::vec3 PerspCamera::GenerateRayOrigin(float u, float v) {
        return viewPoint;
    }

    glm::vec3 PerspCamera::GenerateRayDirection(float u, float v) {
        return -d*(this->w) + u*(this->u)+ v*(this->v);
    }
