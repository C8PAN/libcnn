#ifndef INST_TEMPLATE_HPP_
#define INST_TEMPLATE_HPP_

#define INST_CLASS(class_name) \
template class classname<float>; \
template class classname<double>; \
template class classname<int>;

#endif
