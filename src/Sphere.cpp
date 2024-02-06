#include "../include/Sphere.hpp"
#include "../include/HitRecord.hpp"
#include <glm/geometric.hpp>
#include <cmath>
#include <algorithm>


    Sphere::Sphere(glm::vec3 origin, float radius) : Surface(origin), radius(radius) {}

    HitRecord Sphere::hit(Ray &ray, float t0, float t1) { // returns t value 

        // compute discriminate | (d • (e - c))^2 - (d • d)((e - c)•(e - c) - R^2)
        float dis = pow(glm::dot(ray.getDirection(), (ray.getOrigin() - origin)), 2) 
                    - glm::dot(ray.getDirection(), ray.getDirection()) //
                    *(glm::dot((ray.getOrigin() - origin), (ray.getOrigin() - origin)))
                    - pow(radius, 2);
        
        // TODO: Check discriminate values
        if (dis < 0) { // no intersection
            return HitRecord(this, INFINITY, glm::vec3(0,0,0));
        }
        else if (dis == 0) { // one solution, where ray grazes sphere
            float t = (glm::dot(-(ray.getDirection()), (ray.getOrigin() - origin)) + sqrt(dis)) 
                     / glm::dot(ray.getDirection(), ray.getDirection());
            return HitRecord(this, t, (ray.evaluate(t) - origin) * 2.0f);
        }

        // Two solutions, entry and exit points of sphere

        // !! may need to check if values are within interval !!

        float solution1 = (glm::dot(-(ray.getDirection()), (ray.getOrigin() - origin)) + sqrt(dis)) 
                     / glm::dot(ray.getDirection(), ray.getDirection());
        
        float solution2 = (glm::dot(-(ray.getDirection()), (ray.getOrigin() - origin)) - sqrt(dis)) 
                     / glm::dot(ray.getDirection(), ray.getDirection());

        float t = std::min(solution1, solution2);

        return HitRecord(this, t, (ray.evaluate(t) - origin) * 2.0f);

    }
