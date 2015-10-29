#include <cmath>
#include <iostream>
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


template<typename DT>
void conv_kernel(DT* src, const vector<int>& src_shape,
                 DT* kernel, const vector<int>& kernel_shape,
                 DT* dst) {
  // memory allocated before function
  int dst_rows = src_shape[1] - kernel_shape[1] + 1;
  int dst_cols = src_shape[0] - kernel_shape[0] + 1;

  for(int j = 0; j < dst_cols; ++j) {
    for(int i = 0; i < dst_rows; ++i) {
      // index calculation:
      // for pixel at [i, j], denote by Dij,
      //   Dij = Iij                   * K00                 + Ii(j+1)     * K01 + ... + Ii(j+kernel_cols-1)                 * K0(kernel_cols-1) +
      //         I(i+1)j               * K10                 + I(i+1)(j+1) * K11 + ... + I(i+1)(j+kernel_cols-1)             * K1(kernel_cols-1) +
      //          ...... +
      //         I(i+kernel_rows-1)j * K(kernel_rows-1)0 + ...                         + I(i+kernel_rows-1)(j+kernel_cols-1) * K(kernel_rows-1)(kernel_cols-1);

      // Destination : pixel position [i, j] --> array index j*dst_rows+i;
      // Image source: pixel position [i, j] --> array index j*image_rows+i;
      // Kernel      : pixel position [i, j] --> array index j*kernel_rows+i;
      dst[j*dst_rows+i] = 0;
      for(int l = 0; l < kernel_shape[0]; ++l) {
        for(int k = 0; k < kernel_shape[1]; ++k) {
          dst[j*dst_rows+i] += src[(j+l)*src_shape[1]+(i+k)] * kernel[l*kernel_shape[1]+k];
        }
      }
    }
  }
}

template void conv_kernel(int* src, const vector<int>& src_shape, 
                          int* kernel, const vector<int>& kernel_shape,
                          int* dst);
template void conv_kernel(float* src, const vector<int>& src_shape,
                          float* kernel, const vector<int>& kernel_shape,
                          float* dst);
template void conv_kernel(double* src, const vector<int>& src_shape,
                          double* kernel, const vector<int>& kernel_shape,
                          double* dst);

template<typename DT>
void conv(DT* src, const vector<int>& src_shape,
          DT* kernel, const vector<int>& kernel_shape,
          DT* dst) {
  // TODO:assume that src_shape[1] == kernel_shape[1]
  // calculate dst shape
  int dst_nums = src_shape[0];
  int dst_chas = kernel_shape[0];
  int dst_cols = src_shape[2] - kernel_shape[2] + 1;
  int dst_rows = src_shape[3] - kernel_shape[3] + 1;

  vector<int> src_subshape {src_shape[2], src_shape[3]};
  vector<int> kernel_subshape {kernel_shape[2], kernel_shape[3]};

  unsigned int src_step_dim0 = src_shape[1] * src_shape[2] * src_shape[3];
  unsigned int src_step_dim1 = src_shape[2] * src_shape[3];
  unsigned int kernel_step_dim0 = kernel_shape[1] * kernel_shape[2] * kernel_shape[3];
  unsigned int kernel_step_dim1 = kernel_shape[2] * kernel_shape[3];
  unsigned int dst_step_dim0 = dst_chas * dst_cols * dst_rows;
  unsigned int dst_step_dim1 = dst_cols * dst_rows;

  for(int i = 0; i < src_shape[0]; ++i) {
    for(int j = 0; j < kernel_shape[0]; ++j) {
      int dst_idx = i * dst_step_dim0 + j * dst_step_dim1;
      DT* temp_sum = new DT[dst_cols*dst_rows];
      for(int k = 0; k < kernel_shape[1]; ++k) {
        int src_idx = i * src_step_dim0 + k * src_step_dim1;
        int kernel_idx = j * kernel_step_dim0 + k * kernel_step_dim1;
        conv_kernel<DT>(src+src_idx, src_subshape, kernel+kernel_idx, kernel_subshape, temp_sum);
        for(int l = 0; l < dst_cols; ++l) {
          for(int m = 0; m < dst_rows; ++m) {
            (dst+dst_idx)[l*dst_rows+m] += temp_sum[l*dst_rows+m];
          }
        }
      }
    }
  }
}


template void conv(int* src, const vector<int>& src_shape,
                   int* kernel, const vector<int>& kernel_shape,
                   int* dst);
template void conv(float* src, const vector<int>& src_shape,
                   float* kernel, const vector<int>& kernel_shape,
                   float* dst);
template void conv(double* src, const vector<int>& src_shape,
                   double* kernel, const vector<int>& kernel_shape,
                   double* dst);

} // namespace libcnn
