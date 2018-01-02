#pragma once
#include "IntroToAlgorithm.h"


void main()
{
	vector<int>a = { 1,0,1,1};
	vector<int>b = { 1,1,1,1};
	auto c = binary_add(a, b);
	for (auto i : c)
	{
		cout << i << " ";
	}
	cout << endl;

	system("pause");
}