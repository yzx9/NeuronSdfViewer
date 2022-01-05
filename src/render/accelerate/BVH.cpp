#include <vector>
#include "BVH.hpp"
#include "Bound3.hpp"
#include "Bound3Intersect.hpp"

BVH::BVH(std::unique_ptr<Object> object)
    : aabb(object->build_bound3()), object(std::move(object)), left(nullptr), right(nullptr)
{
}

BVH::BVH(std::unique_ptr<BVH> left, std::unique_ptr<BVH> right)
    : aabb(Bound3::union_bound3(left->aabb, right->aabb)), object(nullptr), left(std::move(left)), right(std::move(right))
{
}

std::unique_ptr<BVH> BVH::build(std::vector<std::unique_ptr<Object>> objects)
{
    std::vector<std::unique_ptr<BVH>> bounds;
    bounds.reserve(objects.size());
    for (auto& object : objects) {
        auto bvh = std::make_unique<BVH>(std::move(object));
        bounds.emplace_back(std::move(bvh));
    }

    return BVH::build(bounds, 0, bounds.size() - 1, 0);
}

using GetBoundVal = std::function<int(std::unique_ptr<BVH>&)>;

void quick_partion(
    std::vector<std::unique_ptr<BVH>>& bounds,
    const int &left,
    const int &right,
    int k,
    const GetBoundVal &val
) {
    if (left >= right) {
        return;
    }

    auto i = left;
    auto j = right;

    while (i < j) {
        std::unique_ptr<BVH> bound = std::move(bounds[i]);

        while (i < j && val(bounds[j]) > val(bound))
            j--;

        if (i < j && val(bounds[j]) <= val(bound))
            bounds[i++] = std::move(bounds[j]);

        while (i < j && val(bounds[i]) < val(bound))
            i++;

        if (i < j && val(bounds[i]) >= val(bound))
            bounds[j--] = std::move(bounds[i]);

        bounds[i] = std::move(bound);
    }

    int mid = (left + right) / 2;
    if (i < k)
    {
        quick_partion(bounds, i + 1, right, k - i, val);
    }
    else if (i > mid)
    {
        quick_partion(bounds, left, i - 1, k, val);
    }
}

std::unique_ptr<BVH> BVH::build(std::vector<std::unique_ptr<BVH>> &bounds, int left, int right, int depth)
{
    if (left >= right) {
        return std::move(bounds[left]);
    }

    constexpr auto getX = [](const std::unique_ptr<BVH>& bound) {
        return bound->aabb->min().x();
    };

    constexpr auto getY = [](const std::unique_ptr<BVH>& bound) {
        return bound->aabb->min().x();
    };

    constexpr auto getZ = [](const std::unique_ptr<BVH>& bound) {
        return bound->aabb->min().z();
    };

    GetBoundVal val;
    switch (depth % 3)
    {
    case 0: val = getX;
    case 1: val = getY;
    case 2: val = getZ;
    };

    int mid = (left + right) / 2;
    quick_partion(bounds, left, right, mid, val);
    std::unique_ptr<BVH> lchild = BVH::build(bounds, left, mid, depth + 1);
    std::unique_ptr<BVH> rchild = BVH::build(bounds, mid + 1, right, depth + 1);
    return std::make_unique<BVH>(std::move(lchild), std::move(rchild));
}

Bound3Intersect BVH::intersect_ray(const Ray& ray) const
{
    auto intersect = aabb->intersect_ray(ray);
    if (!intersect.happend)
    {
        return Bound3Intersect();
    }

    if (object)
    {
        if (object->intersect_ray(ray))
        {
            // should be another intersect
            return Bound3Intersect(0.0f, 0.0f);
        }

        return Bound3Intersect();
    }

    auto left = this->left->intersect_ray(ray);
    auto right = this->right->intersect_ray(ray);
    if (!left.happend && !right.happend)
    {
        return Bound3Intersect();
    }

    // should be another intersect
    return Bound3Intersect(0.0f, 0.0f);
}
