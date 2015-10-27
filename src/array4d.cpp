#include <iostream>
#include "array4d.hpp"
#include "inst_template.hpp"
using namespace libcnn;

namespace libcnn {

/* default constructor, tested */
template<typename DT>
Array4D<DT>::Array4D():
  value_(nullptr), shape_(std::vector<int>(4, 0)) {}

/* copy construnctor, tested */
template<typename DT>
Array4D<DT>::Array4D(const Array4D& src):
  shape_(src.shape_) {
    // allocate memory
    value_ = new DT[src.get_size()];

    // iteratively copy value from source
    for(int i = 0; i < src.get_size(); ++i) {
      value_[i] = src.value_[i];
    }
}

/* constructor, tested */
template<typename DT>
Array4D<DT>::Array4D(const vector<int>& shape):
  shape_(shape) {
    // allocate memory
    value_ = new DT[shape[0]*shape[1]*shape[2]*shape[3]];
}
 
/* constructor (overloaded), tested */
template<typename DT>
Array4D<DT>::Array4D(const vector<int>& shape, DT* const value):
  shape_(shape) {
    // assume that shape and size of value matches
    value_ = value; 
}

/* destructor, tested */
template<typename DT>
Array4D<DT>::~Array4D() {
  delete []value_;
}
 
/* get value, tested */
template<typename DT>
DT* Array4D<DT>::get_value() const {
  return value_;
}


/* get shape, tested */
template<typename DT>
vector<int> Array4D<DT>::get_shape() const {
  return shape_;
}

/* get size, tested */
template<typename DT>
int Array4D<DT>::get_size() const {
  return shape_[0]*shape_[1]*shape_[2]*shape_[3];
}

/* set value, tested */
template<typename DT>
void Array4D<DT>::set_value(DT* const new_value, const int new_size) {
  // allocate memory
  value_ = new DT[new_size];
  value_ = new_value;   
}
 
/* set shape */
template<typename DT>
void Array4D<DT>::set_shape(const vector<int>& new_shape) {
   shape_ = new_shape;
}

/* overload operator = */
template<typename DT>
Array4D<DT>& Array4D<DT>::operator=(const Array4D<DT>& src) {
  shape_ = src.shape_;
  int size = get_size();
  value_ = new DT[size];
  for(int i = 0; i < size; ++i) {
    value_[i] = src.value_[i];
  }  
  return *this;
}

/* overload operator + */
template<typename DT>
Array4D<DT>& Array4D<DT>::operator+(const Array4D<DT>& src) {
  // assume that their shape matches
  int size = get_size();
  for(int i = 0; i < size; ++i) {
    value_[i] += src.value_[i];
  }
  return *this;
}


/* overload operator - */
template<typename DT>
Array4D<DT>& Array4D<DT>::operator-(const Array4D<DT>& src) {
  // assume that their shape matches
  int size = get_size();
  for(int i = 0; i < size; ++i) {
    value_[i] -= src.value_[i]; 
  } 
  return *this;
}


INST_CLASS(Array4D); // instantiate class Array4D

} // namespace libcnn
