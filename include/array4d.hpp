#ifndef LIBCNN_ARRAY4D_HPP_
#define LIBCNN_ARRAY4D_HPP_
#include <vector>

using std::vector;

namespace libcnn {

template<typename DT>
class Array4D {
  private:
    vector<int> shape_;
    int dim0_;            // number of examples
    int dim1_;            // number of channels
    int dim2_;            // number of columns
    int dim3_;            // number of rows
    DT* value_;

  public:
    Array4D();                         
    Array4D(const Array4D& src);
    Array4D(const vector<int>& shape);
    Array4D(const vector<int>& shape, DT* const value);
     ~Array4D();

    DT* get_value() const;
    vector<int> get_shape() const; 
    int get_dim(const int axes) const;
    int get_size() const; 

    void set_value(DT* const new_value, const int new_size); 
    void set_shape(const vector<int>& new_shape);
    
    Array4D<DT>& operator=(const Array4D<DT>& src); 
    Array4D<DT>& operator+(const Array4D<DT>& src);
    Array4D<DT>& operator-(const Array4D<DT>& src); 
}; // class Array4d
} // namespace libcnn
#endif
