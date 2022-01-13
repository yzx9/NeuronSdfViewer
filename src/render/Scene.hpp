#pragma once
#include <limits>
#include <memory>
#include <vector>
#include <Eigen/Dense>
#include "Ray.hpp"
#include "object/Object.hpp"
#include "accelerate/BVH.hpp"

class Scene
{
public:
    Scene() : objects(), bvh(nullptr){};

    Eigen::Vector3f cast_ray(const Ray &ray) const
    {
        auto intersect = intersect_ray(ray);
        if (intersect.happend)
            return {1.0f, 1.0f, 1.0f};

        // TODO: Material
        return {0.0f, 0.0f, 0.0f};
    };

    void add(std::unique_ptr<Object> obj) { objects.emplace_back(std::move(obj)); };

    void build_bvh() { bvh = BVH::build(std::move(objects)); };

private:
    std::vector<std::unique_ptr<Object>> objects;

    std::unique_ptr<BVH> bvh;

    Intersect intersect_ray(const Ray &ray) const
    {
        if (bvh)
            return bvh->intersect_ray(ray);

        Intersect intersect{};
        for (const auto &obj : objects)
            if (auto inter = obj->intersect_ray(ray); inter.happend && inter.t < intersect.t)
                intersect = inter;

        return intersect;
    };
};
