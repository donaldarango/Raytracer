#ifndef SURFACE_H
#define SURFACE_H

#include <glm/vec3.hpp>
#include "Ray.hpp"
#include "Material.hpp"

class HitRecord;
class Material;

class Surface {
public:
    glm::vec3 origin;
    Material material;

    Surface(glm::vec3 origin, Material &material) : origin(origin), material(material) {}

    virtual HitRecord hit(Ray &ray, float t0, float t1) = 0;
};

#endif