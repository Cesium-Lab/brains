// #include "core/isolation-layer/Eigen.h"
// #include <ArduinoEigen.h>

// namespace Cesium {

// using EV3 = Eigen::Vector3f;

// static inline EV3 toEigen(const Vector3f& v) {
//     return EV3(v.x, v.y, v.z);
// }

// static inline Vector3f fromEigen(const EV3& v) {
//     return Vector3f(v.x(), v.y(), v.z());
// }

// float Vector3f::norm() const {
//     return toEigen(*this).norm();
// }

// Vector3f Vector3f::normalized() const {
//     return fromEigen(toEigen(*this).normalized());
// }

// Vector3f Vector3f::operator+(const Vector3f& rhs) const {
//     return fromEigen(toEigen(*this) + toEigen(rhs));
// }

// Vector3f Vector3f::operator-(const Vector3f& rhs) const {
//     return fromEigen(toEigen(*this) - toEigen(rhs));
// }

// Vector3f Vector3f::operator*(float s) const {
//     return fromEigen(toEigen(*this) * s);
// }

// float& Vector3f::operator[](int i) {
//     // no UB, no pointer casting
//     switch (i) {
//         case 0: return x;
//         case 1: return y;
//         case 2: return z;
//         default:
//             // You decide behavior:
//             // 1) trap
//             // 2) clamp
//             // 3) return x
//             // 4) assert (desktop only)

//             __builtin_trap(); // best for embedded
//     }
// }

// const float& Vector3f::operator[](int i) const {
//     switch (i) {
//         case 0: return x;
//         case 1: return y;
//         case 2: return z;
//         default:
//             __builtin_trap();
//     }
// }

// } // namespace Cesium
