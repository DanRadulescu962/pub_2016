#pragma once
#ifndef TEM
#define TEM

#include <iostream>
#include <vector>
using namespace std;

template<class T>
using Map = vector<vector<T>>;

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
		result[i].resize(n);
		if (result[i].empty())
		{
			cout << "FATAL ERROR! Not enough memory!\n";
			abort();
		}
	}
	return result;
}

#endif
