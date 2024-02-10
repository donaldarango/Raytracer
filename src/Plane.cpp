#include "../include/Plane.hpp"
#include "../include/HitRecord.hpp"
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>


    Plane::Plane(glm::vec3 origin, Material &material, glm::vec3 normal) 
        : Surface(origin, material), normal(glm::normalize(normal)) {}

    HitRecord Plane::hit(Ray &ray, float t0, float t1) { // returns t value 

        // float tolerance = pow(0.01,-12);
        float tolerance = 0;


        float numerator = glm::dot(normal, origin - ray.getOrigin());
        // std::cout << "num: " << numerator << std::endl;
        float denominator = glm::dot(normal, ray.getDirection());
        // std::cout << "denom: "<< denominator << std::endl;

        float t = numerator/denominator;

        // std::cout << t << std::endl;
        if (t < t0 - tolerance || t > t1 || denominator == 0)
            return HitRecord(this, INFINITY, normal);
        
        return HitRecord(this, t, normal);
    }