module;
#include <limits>
#include <Eigen/Dense>
export module Render.Ray;

export class Ray
{
public:
    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction);

    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, float max);

    Eigen::Vector3f operator()(float t) const;

    const Eigen::Vector3f& get_origin() const;

    const Eigen::Vector3f& get_direction() const;

    bool is_valid() const;

    bool is_valid(float t) const;

    void set_t_max(float t_max);

private:
    Eigen::Vector3f origin;

    Eigen::Vector3f direction;

    float tMax;
};

constexpr auto floatInfinity = std::numeric_limits<float>::infinity();

Ray::Ray(Eigen::Vector3f origin, Eigen::Vector3f direction)
    : Ray(origin, direction, floatInfinity)
{
}

Ray::Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, float tMax)
    : origin(origin), direction(direction), tMax(tMax)
{
}

const Eigen::Vector3f& Ray::get_origin() const
{
    return origin;
}

const Eigen::Vector3f& Ray::get_direction() const
{
    return direction;
}

Eigen::Vector3f Ray::operator()(float t) const
{
    return origin + direction * t;
}

bool Ray::is_valid() const
{
    return tMax == floatInfinity || tMax > 0;
}

bool Ray::is_valid(float t) const
{
    return tMax == floatInfinity || tMax - t > std::numeric_limits<float>::epsilon();
}

void Ray::set_t_max(float t_max)
{
    this->tMax = t_max;
}
