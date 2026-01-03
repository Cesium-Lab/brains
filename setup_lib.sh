SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd ${SCRIPT_DIR}/src/third-party

# Some directories are not needed for embedded stuff
git clone --depth 1 https://gitlab.com/libeigen/eigen.git
rm -r ${SCRIPT_DIR}/src/third-party/eigen/bench
rm -r ${SCRIPT_DIR}/src/third-party/eigen/blas
rm -r ${SCRIPT_DIR}/src/third-party/eigen/demos
rm -r ${SCRIPT_DIR}/src/third-party/eigen/doc
rm -r ${SCRIPT_DIR}/src/third-party/eigen/failtest
rm -r ${SCRIPT_DIR}/src/third-party/eigen/lapack
rm -r ${SCRIPT_DIR}/src/third-party/eigen/test
rm -r ${SCRIPT_DIR}/src/third-party/eigen/scripts
rm -r ${SCRIPT_DIR}/src/third-party/eigen/unsupported

cd ${SCRIPT_DIR}/lib/
git clone --depth 1 https://github.com/ETLCPP/etl.git
mv "${SCRIPT_DIR}/lib/etl" "${SCRIPT_DIR}/lib/Embedded Template Library"