#pragma once

#include "third-party/eigen/Eigen/Dense" // Won't work doing <Eigen/Dense> manually for some reason 

namespace Cesium {
    using Vector3f = Eigen::Vector3f;
    using Quaternionf = Eigen::Quaternionf;
    using Matrix3f = Eigen::Matrix3f;
    using Matrix6f = Eigen::Matrix<float,6,6>;
}