
//Pack of functions helps for serving creation and process dynamic arrays

template<typename T>
void create_array(T ** &ar, unsigned int h, unsigned int w, bool randomize = false);

template<typename T>
void randomize_array(T ** ar, unsigned int h, unsigned int w, int min =0, int max=100);

template<typename T>
void destroy_array(T ** &ar, unsigned int & h);

template<typename T>
void fill_array(T ** ar, unsigned int h, unsigned int w, const T & value);

#include"dynamic_array.inl"
