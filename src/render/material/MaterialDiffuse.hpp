#pragma once
#include <numbers>
#include <cmath>
#include <Eigen/Dense>
#include "Material.hpp"
#include "../../utils/random.hpp"

class MaterialDiffuse : public Material
{
public:
	MaterialDiffuse(Eigen::Vector3f k_d) : Material(MaterialType::Diffuse), k_d(k_d) {};

	bool has_emission() const override { return false; };

    Eigen::Vector3f calc_brdf(Eigen::Vector3f normal, Eigen::Vector3f in, Eigen::Vector3f out) const override
    {
        // calculate the contribution of diffuse model
        auto cosalpha = normal.dot(out);
        if (cosalpha <= 0.0f)
            return { 0.0f, 0.0f, 0.0f };

        auto diffuse = k_d / std::numbers::pi;
        return diffuse;
    };

    Eigen::Vector3f sample(Eigen::Vector3f normal, Eigen::Vector3f in) const override 
    {
        // uniform sample on the hemisphere
        auto x_1 = get_random_float();
        auto x_2 = get_random_float();
        auto z = std::abs(1.0f - 2.0f * x_1);
        auto r = std::sqrt(1.0f - z * z);
        auto phi = static_cast<float>(2 * std::numbers::pi_v<float> * x_2);
        Eigen::Vector3f local{ r * std::cos(phi), r * std::sin(phi), z };
        return to_world(local, normal);
    };

    Eigen::Vector3f at(double u, double v) const override { return k_d; };

protected:
    Eigen::Vector3f k_d;

    Eigen::Vector3f to_world(const Eigen::Vector3f& a, const Eigen::Vector3f& N) const {
        Eigen::Vector3f C;
        if (std::abs(N.x()) > std::abs(N.y()))
        {
            auto lenInv = 1.0f / std::sqrt(N.x() * N.x() + N.z() * N.z());
            C = Eigen::Vector3f(N.z() * lenInv, 0.0f, -N.x() * lenInv);
        }
        else
        {
            auto lenInv = 1.0f / std::sqrt(N.y() * N.y() + N.z() * N.z());
            C = Eigen::Vector3f(0.0f, N.z() * lenInv, -N.y() * lenInv);
        }
        auto B = C.cross(N);
        return a.x() * B + a.y() * C + a.z() * N;
    }
};
