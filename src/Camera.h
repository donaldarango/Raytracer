#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp> 

class Camera {
public:
// Camera
//   viewpoint, camera,basis
//   resolution
//   depth
//   left, right, top

    Camera();


private:
    // Position
    glm::vec3 viewpoint; // e, position of the camera
    // Camera Basis
    float u;
    float v;
    float w;
    // Resolution
    int width; 
    int height;
    


    
};

#endif