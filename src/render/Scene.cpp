#include "Scene.hpp"

void Scene::add(std::unique_ptr<Object> obj)
{
    auto tuple = std::make_tuple<std::unique_ptr<Object>, Bound3>(std::move(obj), obj->get_bound3());
    objects.emplace_back(std::move(tuple));
}

Eigen::Vector3f Scene::cast_ray(Ray ray) const
{
    for (const auto& [obj, bound3] : objects) {
        const auto intersect = bound3.intersect_ray(ray);

        if (intersect.happend && obj->intersect_ray(ray, intersect.tMin, intersect.tMax)) {
            return { 1.0f, 1.0f, 1.0f };
        }
    }

    return { 0.0f, 0.0f, 0.0f };
}
