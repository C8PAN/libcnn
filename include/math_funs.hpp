#ifndef LIBCNN_MATH_FUNS_HPP_
#define LIBCNN_MATH_FUNS_HPP_

#include <cmath>
#include <vector>

using std::vector;

namespace libcnn {

template<typename DT>
DT relu(const DT& src);

template<typename DT>
double sigmoid(const DT& src);

template<typename DT>
void conv_kernel(DT* src, const vector<int>& src_shape,
                 DT* kernel, const vector<int>& kernel_shape,
                 DT* dst);


template<typename DT>
void conv(DT* src, const vector<int>& src_shape, 
          DT* kernel, const vector<int>& kernel_shape,
          DT* dst);

} // namesapce libcnn
#endif // math.hpp
