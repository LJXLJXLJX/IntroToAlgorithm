#include "stdafx.h"
#include "IntroToAlgorithm.h"


void main()
{
	vector<int>a = {16,14,10,8,7,9,3,2,4,1};
	Heap *heap = new Heap(a);
	heap->heap_sort();
	for (auto i : heap->heap_vector)
		cout << i << " ";
	cout << endl;
	system("pause");
}