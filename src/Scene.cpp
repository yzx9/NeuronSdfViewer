#include "Scene.hpp"

Scene::Scene(int width, int height)
    : height(height), width(width), objects()
{
}

void Scene::add(std::unique_ptr<Object> obj)
{
}

Eigen::Vector3f Scene::cast_ray(std::unique_ptr<Object> obj)
{
    return { 0.0f, 0.0f, 0.0f };
}
