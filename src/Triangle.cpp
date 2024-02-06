#include "../include/Triangle.hpp"
#include "../include/HitRecord.hpp"
#include <glm/geometric.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>


    Triangle::Triangle(glm::vec3 origin, glm::vec3 color, glm::vec3 a, glm::vec3 v, glm::vec3 c) : Surface(origin, color), a(a), b(b), c(c) {}

    HitRecord Triangle::hit(Ray &ray, float t0, float t1) { // returns t value 

        

    }
