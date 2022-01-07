module;
#include <memory>
#include <vector>
#include <limits>
#include <Eigen/Dense>
export module Render.Scene;

import Render.Ray;
import Render.Accelerate.BVH;
import Render.Intersect;
import World.Objects.Object;

export class Scene
{
public:
    Scene();

    Eigen::Vector3f cast_ray(const Ray& ray) const;

    void add(std::unique_ptr<Object> obj);

    void build_bvh();

private:
    std::vector<std::unique_ptr<Object>> objects;

    std::unique_ptr<BVH> bvh;

    Intersect intersect_ray(const Ray& ray) const;
};

Scene::Scene() : objects(), bvh(nullptr) {}

void Scene::add(std::unique_ptr<Object> obj)
{
    objects.emplace_back(std::move(obj));
}

void Scene::build_bvh()
{
    bvh = BVH::build(std::move(objects));
}

Intersect Scene::intersect_ray(const Ray& ray) const
{
    if (bvh)
        return bvh->intersect_ray(ray);

    Intersect intersect{};
    for (const auto& obj : objects)
    {
        if (auto inter = obj->intersect_ray(ray); inter.happend && inter.t < intersect.t)
            intersect = inter;
    }

    return intersect;
}

Eigen::Vector3f Scene::cast_ray(const Ray& ray) const
{
    auto intersect = intersect_ray(ray);
    if (intersect.happend)
        return { 1.0f, 1.0f, 1.0f };

    // TODO: Material
    return { 0.0f, 0.0f, 0.0f };
}

