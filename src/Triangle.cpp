#include "../include/Triangle.hpp"
#include "../include/HitRecord.hpp"
#include <glm/geometric.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>



    Triangle::Triangle(glm::vec3 origin, Material &material, glm::vec3 vertexA, glm::vec3 vertexB, glm::vec3 vertexC) 
        : Surface(origin, material), vertexA(vertexA), vertexB(vertexB), vertexC(vertexC) {}

    HitRecord Triangle::hit(Ray &ray, float t0, float t1) { // returns t value 

        float j = vertexA.x - ray.getOrigin().x;
        float k = vertexA.y - ray.getOrigin().y;
        float l = vertexA.z - ray.getOrigin().z;

        float a = vertexA.x - vertexB.x;
        float b = vertexA.y - vertexB.y;
        float c = vertexA.z - vertexB.z;

        float d = vertexA.x - vertexC.x;
        float e = vertexA.y - vertexC.y;
        float f = vertexA.z - vertexC.z;

        float g = ray.getDirection().x;
        float h = ray.getDirection().y;
        float i = ray.getDirection().z;

        // operation reducing equations
        float ei_hf = (e*i) - (h*f);
        float gf_di = (g*f) - (d*i);
        float dh_eg = (d*h) - (e*g);
        float ak_jb = (a*k) - (j*b);
        float jc_al = (j*c) - (a*l);
        float bl_kc = (b*l) - (k*c);

        float M = a*(ei_hf) + b*(gf_di) + c*(dh_eg);

        
        float t = -(f*(ak_jb) + e*(jc_al) + d*(bl_kc)) / M;
        if ((t < t0) || (t > t1))
            return HitRecord(this, INFINITY, glm::vec3(0,0,0));


        float gamma = (i*(ak_jb) + h*(jc_al) + g*(bl_kc)) / M;
        if ((gamma < 0) || (gamma > 1))
            return HitRecord(this, INFINITY, glm::vec3(0,0,0));


        float beta = (j*(ei_hf) + k*(gf_di) + l*(dh_eg)) / M;
        if ((beta < 0) || (beta > 1 - gamma))
            return HitRecord(this, INFINITY, glm::vec3(0,0,0));

        return HitRecord(this, t, glm::normalize(glm::cross(vertexB - vertexA, vertexC - vertexA)));

    }
