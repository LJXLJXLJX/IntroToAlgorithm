#pragma once
#include "IntroToAlgorithm.h"


void main()
{
	vector<double> a = { 6.6,2.3,6,1,2,8.88,9.3,2.5,3 };
	random_quick_sort(a, 0, 8);
	for (auto i : a)
	{
		cout << i << '\t';
	}

	cout << endl;
	system("pause");
}