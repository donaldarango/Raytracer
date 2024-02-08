#include "../include/OrthoCamera.hpp"
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/perpendicular.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


    OrthoCamera::OrthoCamera(glm::vec3 viewPoint, glm::vec3 viewDir, glm::vec3 upward, float width, float height) 
        : Camera(viewPoint, viewDir, upward, width, height) 
    {
        this->w = -(glm::normalize(viewDir));
        this->u = glm::normalize(glm::cross(upward, viewDir));
        this->v = glm::normalize(glm::cross(viewDir,u));
    }

    glm::vec3 OrthoCamera::GenerateRayOrigin(float u, float v) {
        return viewPoint + (u * this->u) + (v * this->v);
    }

    glm::vec3 OrthoCamera::GenerateRayDirection(float u, float v) {
        return -w;
    }
