
#include <iostream>
using std::rand;
template<typename T>
void create_array(T ** &ar, unsigned int h, unsigned int w, bool randomize)
{
	ar = new T*[h];
	for (size_t i = 0; i < h; i++)
	{
		ar[i] = new T[w];
	}
	if (randomize)
		randomize_array(ar, h, w);
}

template<typename T>
void randomize_array(T ** ar, unsigned int h, unsigned int w, int min, int max)
{
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			ar[i][j] = rand() % (max - min + 1) + min;
		}
	}
}

template<typename T>
void fill_array(T ** ar, unsigned int h, unsigned int w, const T & value)
{
	for (size_t i = 0; i < h; i++)
	{
		for (size_t j = 0; j < w; j++)
		{
			ar[i][j] = value;
		}
	}
}

template<typename T>
void destroy_array(T ** &ar, unsigned int & h)
{
	for (size_t i = 0; i < h; i++)
	{
		delete[]ar[i];
	}
	delete[]ar;
	ar = nullptr;
	h = 0;
}
