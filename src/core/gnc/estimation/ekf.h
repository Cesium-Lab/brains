#pragma once
#include "core/isolation-layer/Eigen.h"

// Generalized EKF based on Algorithms for Decision Making textbook (AA 228)
// https://algorithmsbook.com/files/dm.pdf

namespace Cesium::GNC::Navigation {

/** Extended Kalman Filter State (Nx1 state)
 * - `x`: **State vector** VectorXf [Nx1]
 * - `P`: **State covariance** MatrixXf [NxN] */
template<int N>
struct EkfState {
    VectorXf<N> x;   // Mean vector (Nx1)
    MatrixXf<N, N> P;   // Covariance matrix (NxN)
};


/** EKF for Nx1 state, Mx1 measurements, Ux1 inputs
 * - `f`: state transition model function
 *    f(state_vector: Vectorf [Nx1], input: Vectorf [Ux1]) --> next_state_estimation: Vectorf [Nx1]
 * - `F`: jacobian of state transition model function
 *     F(state_vector: Vectorf [Nx1], input: Vectorf [Ux1]) --> jacobian_F: MatrixXf [NxN]
 * - `h`: observation model function
 *     h(state_vector: Vectorf [Nx1]) --> expected_measurement: Vectorf [Mx1]
 * - `H`: jacobian of observation model function
 *     H(state_vector: Vectorf [Nx1]) --> jacobian_H: MatrixXf [MxN]
 * - `Q`: process noise covariance (float) [NxN]
 * - `R`: measurement noise covariance (float) [MxM]
 */

template<int N, int M, int U>
struct EkfParams {
    VectorXf<N> 
        (*f)(const VectorXf<N>& state, const VectorXf<U>& input); // state transition model getter
    MatrixXf<N, N>
        (*F)(const VectorXf<N>& state, const VectorXf<U>& input); // jacobian of state transition model getter
    VectorXf<M>
        (*h)(const VectorXf<N>& state); // observation model getter
    MatrixXf<M, N>
        (*H)(const VectorXf<N>& state); // jacobian of observation model getter
    MatrixXf<N, N> Q; // process noise covariance
    MatrixXf<M, M> R; // measurement noise covariance
};

template<int N, int M, int U>
class Ekf {
  public:
    Ekf(const EkfParams<N, M, U>& params, const EkfState<N>& initial_state)
        : _params{params}, _state{initial_state} {}

    VectorXf<N> predict(const VectorXf<U>& u) {
        VectorXf<N>& x = _state.x;
        MatrixXf<N, N>& P = _state.P;

        VectorXf<N> x_next = _params.f(x, u);
        MatrixXf<N, N> F = _params.F(x, u);

        P = F * P * F.transpose() + _params.Q;
        x = x_next;

        VectorXf<N> x_next_copy = x_next;

        return x;
    }

    void update(const VectorXf<M>& z) {
        auto& x = _state.x;
        auto& P = _state.P;

        MatrixXf<M, N> H = _params.H(x);

        VectorXf<M> y = z - _params.h(x);
        MatrixXf<M, M> S = H * P * H.transpose() + _params.R;

        MatrixXf<N, M> K = P * H.transpose() * S.completeOrthogonalDecomposition().pseudoInverse();

        x = x + K * y;

        auto _I = MatrixXf<N, N>::Identity();
        P = (_I - K * H) * P * (_I - K * H).transpose()
            + K * _params.R * K.transpose();
    }

    const EkfState<N>& state() const { return _state; }

  private:
    EkfParams<N, M, U> _params;
    EkfState<N> _state;
};


} // namespace Cesium::GNC::Navigation