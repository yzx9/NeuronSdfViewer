#include "Scene.hpp"

void Scene::add(std::unique_ptr<Object> obj)
{
    objects.emplace_back(std::move(obj));
}

Eigen::Vector3f Scene::cast_ray(Ray ray) const
{
    for (auto& obj : objects) {
        if (obj->intesect_ray(ray)) {
            return { 1.0f, 1.0f, 1.0f };
        }
    }

    return { 0.0f, 0.0f, 0.0f };
}
