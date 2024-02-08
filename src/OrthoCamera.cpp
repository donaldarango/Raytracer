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
        std::cout << "w: " << glm::to_string(w) << std::endl;
        this->u = glm::normalize(glm::cross(this->w, upward));
        std::cout << "u: " << glm::to_string(u) << std::endl;
        this->v = glm::normalize(glm::cross(u,w));
        std::cout << "v: " << glm::to_string(v) << std::endl;
    }

    glm::vec3 OrthoCamera::GenerateRayOrigin(float u, float v) {
        return viewPoint + (u * this->u) + (v * this->v);
    }
