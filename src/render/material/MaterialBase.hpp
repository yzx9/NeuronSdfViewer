#pragma once
#include <Eigen/Dense>

enum class MaterialType
{
    Diffuse,

    // light
    LightArea
};

class MaterialBase
{
public:
    MaterialType get_type() const { return type; };

    virtual bool has_emission() const = 0;

    virtual Eigen::Vector3f calc_brdf(Eigen::Vector3f normal, Eigen::Vector3f in, Eigen::Vector3f out) const = 0;

    virtual Eigen::Vector3f sample(Eigen::Vector3f normal, Eigen::Vector3f in) const = 0;

    virtual Eigen::Vector3f at(double u, double v) const = 0;

protected:
    MaterialBase(MaterialType type) : type(type) {};

    MaterialType type;
};
