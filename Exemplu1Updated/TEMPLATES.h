#pragma once
#ifndef TEM
#define TEM

#include <iostream>
#include <vector>
#include<memory>
using namespace std;
using namespace std::tr1;

template<class T>
using Map = vector <shared_ptr<T>>;

template<class T>
Map<T> allocMap(int m, int n)
{
	Map<T> result;
	result.resize(m);
	if (result.empty())
	{
		cout << "FATAL ERROR! Not enough memory!\n";
		abort();
	}

	for (int i = 0; i < m; i++)
	{
		shared_ptr<T> ptr(new T[n], [](T* ptr) {delete[] ptr; });
		result[i] = ptr;
		if (!result[i])
		{
			cout << "FATAL ERROR! Not enough memory!\n";
			abort();
		}
	}
	return result;
}

#endif
