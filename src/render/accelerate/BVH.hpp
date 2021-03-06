#pragma once
#include <vector>
#include <memory>
#include "Accelerate.hpp"
#include "Bound3.hpp"
#include "Bound3Intersect.hpp"
#include "../Intersect.hpp"
#include "../object/Object.hpp"
#include "../../utils/partion.hpp"

class BVH : public Accelerate
{
public:
    static std::unique_ptr<BVH> build(std::vector<std::unique_ptr<Object>> objects)
    {
        std::vector<std::unique_ptr<BVH>> bounds;
        bounds.reserve(objects.size());
        for (auto &object : objects)
            bounds.emplace_back(std::make_unique<BVH>(std::move(object)));

        return BVH::build(bounds, 0, bounds.size() - 1, 0);
    };

    Intersect intersect_ray(const Ray &ray) const override
    {
        auto intersect = aabb->intersect_ray(ray);
        if (!intersect.happend)
            return Intersect();

        if (object)
            return object->intersect_ray(ray, intersect.tMin, intersect.tMax);

        auto left = this->left->intersect_ray(ray);
        auto right = this->right->intersect_ray(ray);

        if (left.happend && right.happend)
            return left.t <= right.t ? left : right;

        if (left.happend)
            return left;

        if (right.happend)
            return right;

        return Intersect();
    };

    BVH(std::unique_ptr<Object> object)
        : aabb(object->build_bound3()), object(std::move(object)), left(nullptr), right(nullptr){};

    BVH(std::unique_ptr<BVH> left, std::unique_ptr<BVH> right)
        : aabb(Bound3::union_bound3(left->aabb, right->aabb)), object(nullptr), left(std::move(left)), right(std::move(right)){};

protected:
    std::unique_ptr<Bound3> aabb;
    std::unique_ptr<Object> object;

    std::unique_ptr<BVH> left;
    std::unique_ptr<BVH> right;

    static std::unique_ptr<BVH> build(std::vector<std::unique_ptr<BVH>> &bounds, int left, int right, int depth)
    {
        using pBVH = std::unique_ptr<BVH>;
        if (left >= right)
            return std::move(bounds[left]);

        constexpr auto getVal = [](int index, const pBVH &bound)
        { return bound->aabb->min()[index] + bound->aabb->max()[index]; };

        auto val = std::bind(getVal, depth % 3, std::placeholders::_1);

        auto mid = (left + right) / 2;
        quick_partion_k<pBVH, float>(bounds, val, left, right, mid);
        pBVH lchild = BVH::build(bounds, left, mid, depth + 1);
        pBVH rchild = BVH::build(bounds, mid + 1, right, depth + 1);
        return std::make_unique<BVH>(std::move(lchild), std::move(rchild));
    };

    void dispose(std::vector<std::unique_ptr<Object>>& objects) override
    {
        if (object)
        {
            objects.emplace_back(std::move(object));
        }
        else
        {
            left->dispose(objects);
            right->dispose(objects);
        }
    };
};
