#pragma once
#ifndef TEM
#define TEM

template <class T>
T** allocMap(int m, int n)
{
	int pause = -1;
	T** Map;
	try
	{
		Map = (T**)malloc(m * sizeof(T*));
		if (!Map)
			throw - 1;
		for (int i = 0; i < m; i++)
		{
			Map[i] = (T*)malloc(n * sizeof(T));
			if (!Map[i])
			{
				pause = i;
				throw - 2;
			}
		}
		return Map;
	}
	catch (int e)
	{
		if (e == -1)
		{
			cout << "Cannot allocate memory!\n";
			Map = NULL;
		}
		else if (e == -1)
		{
			cout << "Cannot allocate memory!\n";
			for (int i = 0; i < pause; i++)
			{
				free(Map[i]);
				Map[i] = NULL;
			}
			free(Map);
			Map = NULL;
		}
		return Map;
	}
}

template <class T>
void freeMap(int m, T** map)
{
	for (int i = 0; i < m; i++)
	{
		free(map[i]);
		map[i] = NULL;
	}
	free(map);
	map = NULL;
}

#endif