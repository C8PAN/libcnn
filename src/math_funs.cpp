#include <cmath>
#include <algorithm>
#include "math_funs.hpp"

using namespace libcnn;

namespace libcnn {

template<typename DT>
DT relu(const DT& x) {
  return std::max(x, DT(0));
}

template int relu<int>(const int& x);
template float relu<float>(const float& x);
template double relu<double>(const double& x);

template<typename DT>
double sigmoid(const DT& x) {
  return 1.0 / (1.0 + std::exp(-x));
}

template double sigmoid(const int& x);
template double sigmoid(const float& x);
template double sigmoid(const double& x);

} // namespace libcnn
