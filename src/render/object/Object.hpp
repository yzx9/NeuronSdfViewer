#pragma once
#include <memory>
#include "../Intersect.hpp"
#include "../Ray.hpp"
#include "../accelerate/Bound3.hpp"
#include "../material/Material.hpp"

class Object
{
public:
    Object(Eigen::Vector3f position) : position(position){};

    virtual ~Object() {};

    virtual Intersect intersect_ray(const Ray &ray) const = 0;

    virtual Intersect intersect_ray(const Ray &ray, const float &tMin, const float &tMax) const = 0;

    virtual std::unique_ptr<Bound3> build_bound3() const = 0;

    void set_material(std::shared_ptr<Material> material) { this->material = material; };

    Eigen::Vector3f get_color_at(double u, double v) const
    {
        if (material)
            return material->at(u, v);

        return { 0.0, 0.0, 0.0 };
    }

protected:
    Eigen::Vector3f position;

    std::shared_ptr<Material> material;
};
