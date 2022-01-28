#pragma once
#include <limits>
#include <memory>
#include <vector>
#include <Eigen/Dense>
#include "Ray.hpp"
#include "object/Object.hpp"
#include "accelerate/Accelerate.hpp"
#include "accelerate/BVH.hpp"

class Scene
{
public:
    Scene() : objects(), accelerate(nullptr){};

    Eigen::Vector3f cast_ray(const Ray &ray) const
    {
        auto intersect = intersect_ray(ray);
        if (!intersect.happend)
            return {0.0f, 0.0f, 0.0f};

        return intersect.color;
    };

    void add(std::unique_ptr<Object> obj) {
        if (accelerate)
        {
            objects = accelerate->dispose();
            accelerate = nullptr;
        }

        objects.emplace_back(std::move(obj));
    };

    void build_bvh() { accelerate = BVH::build(std::move(objects)); };

private:
    std::vector<std::unique_ptr<Object>> objects;

    std::unique_ptr<Accelerate> accelerate;

    Intersect intersect_ray(const Ray &ray) const
    {
        if (accelerate)
            return accelerate->intersect_ray(ray);

        Intersect intersect{};
        for (const auto &obj : objects)
            if (auto inter = obj->intersect_ray(ray); inter.happend && inter.t < intersect.t)
                intersect = inter;

        return intersect;
    };
};
