#ifndef MATH_FUNS_HPP_
#define MATH_FUNS_HPP_

#include <cmath>

namespace libcnn {

template<typename DT>
DT relu(const DT& src);

template<typename DT>
double sigmoid(const DT& src);

} // namesapce libcnn
#endif // math.hpp
