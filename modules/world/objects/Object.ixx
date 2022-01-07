module;
#include <memory>
#include <Eigen/Dense>
export World.Objects.Object;

import Render.Intersect;
import Render.Ray;
import Render.Accelerate.Bound3;

export class Object
{
public:
    Object(Eigen::Vector3f position) : position(position){};

    virtual ~Object() {};

    virtual Intersect intersect_ray(const Ray &ray) const = 0;

    virtual Intersect intersect_ray(const Ray &ray, const float &tMin, const float &tMax) const = 0;

    virtual std::unique_ptr<Bound3> build_bound3() const = 0;

protected:
    Eigen::Vector3f position;
};
