#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp> 

class Camera {
public:

    Camera(glm::vec3 viewPoint, glm::vec3 viewDir, glm::vec3 upward, float width, float height) {
        this->viewPoint = viewPoint; 
        this->viewDir = viewDir;
        this->upward = upward;
        this->l = -10.0f;
        this->r = 10.0f;
        this->b = -10.0f;
        this->t = 10.0f;
    }

    float DeterminePixelU(int i, int imageWidth) {
        return l + (r - l)*(i + 0.5) / imageWidth;
    }

    float DeterminePixelV(int j, int imageHeight) {
        return b + (t - b)*(j + 0.5) / imageHeight;
    }

    virtual glm::vec3 GenerateRayOrigin(float u, float v) = 0;
    virtual glm::vec3 GenerateRayDirection(float u, float v) = 0;

    glm::vec3 getU() {
        return w;
    }
    glm::vec3 getV() {
        return v;
    }
    glm::vec3 getW() {
        return w;
    }
    // Position
    glm::vec3 viewPoint; // e, position of the camera
    glm::vec3 viewDir; // d, LookAt vector
    glm::vec3 upward;
    // Camera Basis
    glm::vec3 u;
    glm::vec3 v;
    glm::vec3 w;
    
    // Top, Bottom, Right, Left points that make up viewing rectangle in u-v plane
    float t;
    float b;
    float r;
    float l;
    
};

#endif