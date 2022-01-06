#include "Scene.hpp"
#include "accelerate/BVH.hpp"

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

    for (const auto& obj : objects)
    {
        if (auto intersect = obj->intersect_ray(ray); intersect.happend)
            return intersect;
    }

    return Intersect();
}

Eigen::Vector3f Scene::cast_ray(const Ray& ray) const
{
    // TODO: Material
    auto intersect = intersect_ray(ray);
    return intersect.happend
        ? Eigen::Vector3f{ 1.0f, 1.0f, 1.0f }
        : Eigen::Vector3f{ 0.0f, 0.0f, 0.0f };
}
