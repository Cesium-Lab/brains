SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

mkdir -p "${SCRIPT_DIR}/src/third-party"

cd "${SCRIPT_DIR}/src/third-party"

# Some directories are not needed for embedded stuff
git clone --depth 1 https://gitlab.com/libeigen/eigen.git
for dir in bench benchmarks blas demos doc failtest lapack test scripts unsupported; do
    rm -rf "${SCRIPT_DIR}/src/third-party/eigen/${dir}"
done

# Wrap EIGEN_OS_MAC definition with #ifndef so the -DEIGEN_OS_MAC=0 build flag
# overrides it — without this, Macros.h redefines it to 1 on Apple hosts and
# Eigen/Core pulls in sys/sysctl.h, which doesn't exist in the ESP32 sysroot.
python3 -c "
import pathlib
p = pathlib.Path('${SCRIPT_DIR}/src/third-party/eigen/Eigen/src/Core/util/Macros.h')
old = '/// \\\internal EIGEN_OS_MAC set to 1 if the OS is MacOS\n#if defined(__APPLE__)\n#define EIGEN_OS_MAC 1\n#else\n#define EIGEN_OS_MAC 0\n#endif'
new = '/// \\\internal EIGEN_OS_MAC set to 1 if the OS is MacOS\n#ifndef EIGEN_OS_MAC\n#if defined(__APPLE__)\n#define EIGEN_OS_MAC 1\n#else\n#define EIGEN_OS_MAC 0\n#endif\n#endif'
p.write_text(p.read_text().replace(old, new, 1))
"

git clone --depth 1 https://github.com/ETLCPP/etl.git
for dir in examples test; do
    rm -rf "${SCRIPT_DIR}/src/third-party/etl/${dir}"
done
mv "${SCRIPT_DIR}/src/third-party/etl" "${SCRIPT_DIR}/src/third-party/Embedded Template Library"