#include "Sphere.hpp"
#include "HitRecord.hpp"
#include <glm/geometric.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>


    Sphere::Sphere(glm::vec3 origin, Material &material, float radius) : Surface(origin, material), radius(radius) {}

    HitRecord Sphere::hit(Ray &ray, float t0, float t1) { // returns t value 

        // compute discriminate | (d • (e - c))^2 - (d • d)((e - c)•(e - c) - R^2)
        
        float B = glm::dot(ray.getDirection(), (ray.getOrigin() - origin)); // d • (e - c)^2
        float A = glm::dot(ray.getDirection(), ray.getDirection()); // (d • d)
        float C = glm::dot((ray.getOrigin() - origin), (ray.getOrigin() - origin)) - pow(radius, 2);

        float discriminate = pow(B, 2) - A*C;
        
        // std::cout << discriminate << std::endl;
        // TODO: Check discriminate values
        if (discriminate < 0) { // no intersection
            return HitRecord(this, INFINITY, glm::vec3(0,0,0));
        }
        else if (discriminate == 0) { // one solution, where ray grazes sphere
            float t = (glm::dot(-(ray.getDirection()), (ray.getOrigin() - origin)) + sqrt(discriminate)) 
                     / glm::dot(ray.getDirection(), ray.getDirection());
            return HitRecord(this, t, (ray.evaluate(t) - origin) * 2.0f);
        }

        // Two solutions, entry and exit points of sphere

        // !! may need to check if values are within interval !!

        float solution1 = (glm::dot(-(ray.getDirection()), (ray.getOrigin() - origin)) + sqrt(discriminate)) 
                     / glm::dot(ray.getDirection(), ray.getDirection());
        
        float solution2 = (glm::dot(-(ray.getDirection()), (ray.getOrigin() - origin)) - sqrt(discriminate)) 
                     / glm::dot(ray.getDirection(), ray.getDirection());


        float min = std::min(solution1, solution2);
        float max = std::max(solution1, solution2);
        float t;
        if (min > t0 && min < t1) {
            t = min;
        }
        else // max is the t value
        {
            t = max;
        }

        return HitRecord(this, t, (ray.evaluate(t) - origin) / radius);

    }
