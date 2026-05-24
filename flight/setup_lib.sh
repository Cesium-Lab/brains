SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

mkdir -p "${SCRIPT_DIR}/src/third-party"

cd "${SCRIPT_DIR}/src/third-party"

# Some directories are not needed for embedded stuff
git clone --depth 1 https://gitlab.com/libeigen/eigen.git
for dir in bench benchmarks blas demos doc failtest lapack test scripts unsupported; do
    rm -rf "${SCRIPT_DIR}/src/third-party/eigen/${dir}"
done

git clone --depth 1 https://github.com/ETLCPP/etl.git
for dir in examples test; do
    rm -rf "${SCRIPT_DIR}/src/third-party/etl/${dir}"
done
mv "${SCRIPT_DIR}/src/third-party/etl" "${SCRIPT_DIR}/src/third-party/Embedded Template Library"