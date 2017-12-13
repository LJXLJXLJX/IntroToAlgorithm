#include "stdafx.h"
#include "IntroToAlgorithm.h"


void main()
{
	vector<int>a = { 2,8,7,1,3,5,6,4 };
	int b = random_quick_sort(a, 0, 7);
	for (auto i : a)
	{
		cout << i << " ";
	}
	cout << endl;

	system("pause");
}