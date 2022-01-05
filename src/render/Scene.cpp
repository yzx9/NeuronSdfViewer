#include "Scene.hpp"
#include "accelerate/BVH.hpp"

Scene::Scene()
    : objects(), bvh(nullptr)
{
}

void Scene::add(std::unique_ptr<Object> obj)
{
    objects.emplace_back(std::move(obj));
}

void Scene::build_bvh()
{
    bvh = BVH::build(std::move(objects));
}

Eigen::Vector3f Scene::cast_ray(const Ray& ray) const
{
    // TODO: Material
    if (bvh) {
        auto intersect = bvh->intersect_ray(ray);
        return intersect.happend
            ? Eigen::Vector3f{ 1.0f, 1.0f, 1.0f }
            : Eigen::Vector3f{ 0.0f, 0.0f, 0.0f };
    }

    for (const auto &obj : objects)
    {
        if (obj->intersect_ray(ray))
        {
            return { 1.0f, 1.0f, 1.0f };
        }
    }

    return { 0.0f, 0.0f, 0.0f };
}
