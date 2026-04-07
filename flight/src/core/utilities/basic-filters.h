#pragma once

#include <stdint.h>

#include "core/isolation-layer/Eigen.h"

namespace Cesium {

// Just like my implementations in GNC Playground
// y is output, x is input, and alpha is the smoothing factor (0 < alpha < 1)

/* 
Templeted so I can have float and vectors
https://en.wikipedia.org/wiki/Low-pass_filter#Simple_infinite_impulse_response_filter
*/
template <typename T>
class LowPassFilter {
  public:
    LowPassFilter(float alpha) : _alpha{alpha}, _y{}, _initialized{false} {}

    T run(const T& x) {
        if (!_initialized) {
            _y = x;
            _initialized = true;
        }
        _y = _alpha * x + (1 - _alpha) * _y;
        return _y;
    }

    T reset(const T& y = T{}) {
        _y = y;
        return _y;
    }

  private:
    float _alpha;
    T _y{};

    bool _initialized;
};

/* 
Templeted so I can have float and vectors
https://en.wikipedia.org/wiki/High-pass_filter#Algorithmic_implementation
*/
template <typename T>
class HighPassFilter {
  public:
    HighPassFilter(float alpha)
        : _alpha{alpha}, _x_prev{}, _y{}, _initialized{false} {}

    T run(const T& x) {
        if (!_initialized) {
            _x_prev = x;
            _initialized = true;
        }
        _y = _alpha * _y + _alpha * (x - _x_prev);
        _x_prev = x;
        return _y;
    }

    T reset(const T& x_prev = T{}, const T& y = T{}) {
        _x_prev = x_prev;
        _y = y;
        return _y;
    }

  private:
    float _alpha;
    T _x_prev{};
    T _y{};

    bool _initialized;
};

} // namespace Cesium