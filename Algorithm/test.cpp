#include "stdafx.h"
#include "IntroToAlgorithm.h"


void main()
{
	vector<int>a = { 2,4,10,14,7,9,3,2,8,1 };
	Heap *heap = new Heap(a);
	heap->build_max_heap();
	for (auto i : heap->heap_vector)
		cout << i << " ";
	cout << endl;
	system("pause");
}