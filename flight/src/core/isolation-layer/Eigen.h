#pragma once

#include "third-party/eigen/Eigen/Dense" // Won't work doing <Eigen/Dense> manually for some reason 

namespace Cesium {
    using Vector3f = Eigen::Vector3f;
    using Quaternionf = Eigen::Quaternionf;
    using Matrix3f = Eigen::Matrix3f;
    using Matrix6f = Eigen::Matrix<float,6,6>;
    template<int N>
    using VectorXf = Eigen::Matrix<float, N, 1>;

    template<int N, int M>
    using MatrixXf = Eigen::Matrix<float, N, M>;
}