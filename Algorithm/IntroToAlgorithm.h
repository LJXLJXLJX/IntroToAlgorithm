#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <limits>
#include <random>


using namespace std;




//2.1-1，2 insertion - sort mode 0为升序
template <typename T>
vector<T> insertion_sort(vector<T> &arr, int mode = 0)
{


	int len = arr.size();
	for (int i = 0; i < len; i++)
	{
		int origin_i = i;
		auto temp = arr[i];
		if (mode == 0)//非降序
			while (i > 0 && temp < arr[i - 1])
				i--;
		if (mode == 1)//非升序
			while (i > 0 && temp > arr[i - 1])
				i--;
		arr.erase(begin(arr) + origin_i);
		arr.insert(begin(arr) + i, temp);
	}
	return arr;
}


//2.1-3 查找问题，在数组A中找到v，返回下标。若不存在v，返回-1
template <typename T>
vector<int> find_out(vector<T> A, T v)
{
	int len = A.size();//容器A长度
	vector<int> result;//返回的下标i
	for (int i = 0; i < len; i++)
	{
		if (v == A[i])
			result.push_back(i);
	}
	if (result.empty())
	{
		cout << "序列中不存在v" << endl;
		return { -1 };
	}
	else
		return result;
}

//2.1-4二进制相加，二进制数都用向量表示
vector<int> binary_add(vector<int> a, vector<int> b);


//2.3-1、2归并排序
template <typename T>
vector<T> merge_two(vector<T> vec1, vector<T> vec2)	//将两组已经排好序的矢量归并
{
	vector<T> reverse_result;	//反转的结果
	vector<T> result;	//输出结果（由于vector只能在尾端做操作 该merge得到的结果reverse_result其实是反转的 再反转一次即可得到正确的结果）
	while (vec1.size() > 0 || vec2.size() > 0)	//没到哨兵牌 比大小后插入
	{
		if (vec1.size() > 0 && vec2.size() > 0)
		{
			if (vec1.back() > vec2.back())
			{
				reverse_result.push_back(vec1.back());
				vec1.pop_back();
			}
			else
			{
				reverse_result.push_back(vec2.back());
				vec2.pop_back();
			}
		}

		else if (vec1.size() == 0)	//vec1到了哨兵牌 插2
		{
			reverse_result.push_back(vec2.back());
			vec2.pop_back();
		}
		else if (vec2.size() == 0)	//vec2到了哨兵牌 插1
		{
			reverse_result.push_back(vec1.back());
			vec1.pop_back();
		}
		else
			cout << "something wrong!!!" << endl;

	}
	//最后做个反转即可得到正确结果
	while (reverse_result.size() != 0)
	{
		result.push_back(reverse_result.back());
		reverse_result.pop_back();
	}

	return result;
}

template <typename T>
vector<T> merge(vector<T>arr)	//归并 依赖于上一个函数
{
	vector<vector<T>> vec_container;//定义一个容纳（基）矢量的矢量

	for (auto i : arr)//将每个值装入每个基矢量中
	{
		vector<T> a;
		a.push_back(i);
		vec_container.push_back(a);
	}
	while (vec_container.size() > 1)
	{
		for (int i = 0; i < vec_container.size() - 1; i++)
		{
			vec_container[i] = merge_two(vec_container[i], vec_container[i + 1]);
			vec_container.erase(vec_container.begin() + i + 1);
		}
	}
	return vec_container[0];
}

//2.3-5 有序数列的二分法查找
template <typename T>
vector<int> bisection_find_out(vector<T> A, T v)
{
	vector<T> section;	//最终段
	int head = 0;		//段头索引
	int tail = A.size() - 1;	//段尾索引
	int offset = A.size() / 2 + A.size() % 2;	//中点偏移
	int center = head + offset - 1;		//中点
	while (v != A[center] && head != center)
	{

		if (v > center)
		{
			head = center + 1;
			offset = (tail - head) / 2 + (tail - head) % 2;
			if (head == tail)
				center = head;
			else
				center = head + offset - 1;
		}
		else
		{
			tail = center;
			offset = (tail - head) / 2 + (tail - head) % 2;
			if (head == tail)
				center = head;
			else
				center = head + offset - 1;
		}

	}
	section.assign(A.begin() + head, A.begin() + tail + 1);
	vector<int> result = find_out(section, v);
	for (auto &i : result)
	{
		i += head;
	}
	return result;

}

//4.1-2 暴力求解最大子数组 返回值为头尾索引以及子数组元素总和（当存在多个最大子数组 找到最靠右的那个）
template <typename T>
vector<T> brainless_find_max_subarray(vector<T> arr)
{
	int sum = 0;	//元素和
	T max_sum = 0;	//最大元素和
	int max_subarray_head = 0;	//最大子数组头
	int max_subarray_tail = 0;	//最大字数组尾
	for (int i = 0; i < arr.size(); i++)
	{
		sum = 0;
		for (int j = i; j < arr.size(); j++)
		{
			sum += arr[j];
			if (sum >= max_sum)
			{
				max_sum = sum;
				max_subarray_head = i;
				max_subarray_tail = j;
			}
		}
	}
	vector<T> result = { T(max_subarray_head),T(max_subarray_tail),max_sum };
	return result;
}

//4.1-3 最大子数组递归法
template <typename T>
vector<T> find_max_crossing_subarray(vector<T> arr, int low, int mid, int high)	//	找到跨中点的最大子数列
{
	T left_sum = 0;
	T right_sum = 0;
	int max_left;
	int max_right;
	T sum;
	vector<T> left_vec(arr.begin() + low, arr.begin() + mid + 1);
	vector<T> right_vec(arr.begin() + mid + 1, arr.begin() + high + 1);
	max_left = brainless_find_max_subarray(left_vec)[0] + low;	//左半最大子数组头
	vector<T> left_max_vec(left_vec.begin() + (max_left - low), left_vec.end());	//到中点的左半最大子数组
	for (auto i : left_max_vec)	//到中点的左半最大子数组元素之和
		left_sum += i;
	max_right = brainless_find_max_subarray(right_vec)[1] + mid + 1;
	vector<T> right_max_vec(right_vec.begin(), right_vec.begin() + (max_right - mid));	//到中点的左半最大子数组
	for (auto i : right_max_vec)//从中点开始右半最大子数组之和
		right_sum += i;
	sum = right_sum + left_sum;
	vector<T> result = { T(max_left) ,T(max_right) ,sum };
	return result;
}

template <typename T>
vector<T> find_max_subarray(vector<T> arr, int low, int high)	//递归求最大子数列
{
	//递归问题要用静态变量，避免重复初始化
	static int left_low;
	static int left_high;
	static T left_sum;
	static int right_low;
	static int right_high;
	static T right_sum;
	static int cross_low;
	static int cross_high;
	static T cross_sum;
	vector<T> result;
	if (high == low)
	{
		result = { T(low),T(high),arr[low] };
		return result;
	}
	else
	{
		int width = high - low + 1;
		int mid = low + width / 2 + width % 2 - 1;
		vector<T> left_result = find_max_subarray(arr, low, mid);
		left_low = int(left_result[0]);
		left_high = int(left_result[1]);
		left_sum = left_result[2];
		vector<T> right_result = find_max_subarray(arr, mid + 1, high);
		right_low = int(right_result[0]);
		right_high = int(right_result[1]);
		right_sum = right_result[2];
		vector<T> cross_result = find_max_crossing_subarray(arr, low, mid, high);
		cross_low = int(cross_result[0]);
		cross_high = int(cross_result[1]);
		cross_sum = cross_result[2];
		if (left_sum >= right_sum && left_sum >= cross_sum)
		{
			result = { T(left_low),T(left_high),T(left_sum) };
			return result;
		}
		else if (right_sum >= left_sum && right_sum >= cross_sum)
		{
			result = { T(right_low),T(right_high),right_sum };
			return result;
		}
		else
		{
			result = { T(cross_low),T(cross_high),cross_sum };
			return result;
		}
	}
}

//4.2 矩阵乘法
//square matrix multiply
template <typename T>
vector<vector<T>> matrix_multiply(vector<vector<T>> A, vector<vector<T>> B)
{
	vector<vector<T>> error_flag = { { 0 } };
	//----判断矩阵A是否为规范的矩阵------
	int m = A.size();//行数
	int n = A[0].size();//第一行的元素数 每一行应该一样
	for (int i = 1; i < m; i++)
	{
		if (A[i].size() != n)
		{
			cout << "输入矩阵A不规范" << endl;
			return error_flag;
		}
	}
	//----------------------------
	//----判断矩阵B是否为规范的矩阵-----
	int a = B.size();
	int b = B[0].size();
	for (int i = 1; i < a; i++)
	{
		if (A[i].size() != b)
		{
			cout << "输入矩阵B不规范" << endl;
			return error_flag;
		}
	}
	//---------------------------------
	//----判断A,B能否做矩阵乘法--------
	if (n != a)
	{
		cout << "A,B不能做矩阵乘法" << endl;
		return error_flag;
	}
	//----------------------------

	//---------做运算----------
	vector<T> initial_row(b, 0);
	vector<vector<T>> C(m, initial_row);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < b; j++)
		{
			for (int k = 0; k < n; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}
//矩阵加法
template <typename T>
vector<vector<T>> matrix_add(vector<vector<T>> A, vector<vector<T>> B)
{
	vector<vector<T>> error_flag = { { 0 } };
	//------判断A,B是否为规范的矩阵--------
	int m = A.size(), n = A[0].size(), a = B.size(), b = B[0].size();
	if (m != a || n != b)
	{
		cout << "A，B阶数不一致" << endl;
		return error_flag;
	}
	for (auto i : A)
	{
		if (i.size() != n)
		{
			cout << "A不是规范的矩阵" << endl;
			return error_flag;
		}
	}
	for (auto i : B)
	{
		if (i.size() != b)
		{
			cout << "B不是规范的矩阵" << endl;
			return error_flag;
		}
	}
	//----------------------------------
	//------------运算---------
	vector<T> sub_initial_row(n, 0);
	vector<vector<T>> C(m, sub_initial_row);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	//-------------------------
	return C;
}
//方阵的分治乘法（分块乘法）阶数必须为2^n
template <typename T>
vector<vector<T>> square_matrix_multiply_recursive(vector<vector<T>> A, vector<vector<T>> B)
{
	int n = A.size();
	vector<vector<T>> error_flag = { { 0 } };
	vector<T> initial_row(n, 0);
	vector<vector<T>> C(n, initial_row);
	//----判断矩阵A,B是否为2^n阶方阵-----
	if (n == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
	}
	else
	{
		float n_float = n;
		while (n_float != 2)
		{
			n_float = sqrt(n_float);
			if (n_float < 2)
			{
				cout << "阶数不符合条件，必须是2^n" << endl;
				return error_flag;
			}
		}
		if (A.size() != B.size())
		{
			cout << "A,B阶数不同" << endl;
			return error_flag;
		}
		//----------------------------------
		//-------判断A,B是否为规范的方阵-----
		for (auto i : A)
		{
			if (i.size() != n)
			{
				cout << "A不是规范的方阵" << endl;
				return error_flag;
			}
		}
		for (auto i : B)
		{
			if (i.size() != n)
			{
				cout << "B不是规范的方阵" << endl;
				return error_flag;
			}
		}

		//-----做运算---------
		//----子矩阵的赋值（复制）----
		/*算法导论此处关于绕开子矩阵的创建与赋值，直接用原始矩阵的下标进行输入的说法纯属扯淡。
		对计算机而言，C++ STL下，根本就没有真正的矩阵数据类型。
		所谓直接用下标运算，还是绕不开新矩阵(vector)的创建与赋值（复制）*/
		int m = n / 2;
		vector<T> sub_initial_row1(m, 0), sub_initial_row2(n - m, 0);
		vector<vector<T>> A11(m, sub_initial_row1), B11(m, sub_initial_row1), C11(m, sub_initial_row1);
		vector<vector<T>> A12(m, sub_initial_row2), B12(m, sub_initial_row2), C12(m, sub_initial_row2);
		vector<vector<T>> A21(n - m, sub_initial_row1), B21(n - m, sub_initial_row1), C21(n - m, sub_initial_row1);
		vector<vector<T>> A22(n - m, sub_initial_row2), B22(n - m, sub_initial_row2), C22(n - m, sub_initial_row2);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + m];
				A21[i][j] = A[i + m][j];
				A22[i][j] = A[i + m][j + m];
				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + m];
				B21[i][j] = B[i + m][j];
				B22[i][j] = B[i + m][j + m];
			}
		}
		//----------------------------------------
		//---------递归运算各子矩阵---------------
		C11 = matrix_add(square_matrix_multiply_recursive(A11, B11), square_matrix_multiply_recursive(A12, B21));
		C12 = matrix_add(square_matrix_multiply_recursive(A11, B12), square_matrix_multiply_recursive(A12, B22));
		C21 = matrix_add(square_matrix_multiply_recursive(A21, B11), square_matrix_multiply_recursive(A22, B21));
		C22 = matrix_add(square_matrix_multiply_recursive(A21, B12), square_matrix_multiply_recursive(A22, B22));
		//--------------------------------
		//-----合并子矩阵------------
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < m; j++)
			{
				C[i][j] = C11[i][j];
				C[i][j + m] = C12[i][j];
				C[i + m][j] = C21[i][j];
				C[i + m][j + m] = C22[i][j];
			}
		}
		//-----------------------------
	}
	return C;
}


//第六章 堆 
/*
只实现了最大堆相关算法
最小堆无非就是照搬套路，改个大于小于
懒得弄了，以后有需要再补上
*/
template <typename	T>
class Heap {
public:
	Heap(const vector<T> &arr)
	{
		Heap::index = 0;
		Heap::heap_size = arr.size();
		Heap::heap_vector = arr;
	}
	//获取当前节点（索引）对应的信息（所处深度 子节点）
	int get_node_information(int index)
	{
		Heap::depth = 0;
		if (index < 0 || index >= heap_size)
		{
			cout << "输入索引错误，不在当前堆范围内" << endl;
			return -1;
		}
		//---------获取（更新）当前节点所在深度---------------
		/*
		深度和索引都是从零开始算起
		每层的头尾节点分别是 2^depth-1 和 2*(2^depth-1)
		*/
		while (1)
		{
			if (index >= pow(2, Heap::depth) - 1 && index <= pow(2, Heap::depth + 1) - 2)
				break;
			Heap::depth++;
		}
		//-----------------------------------------

		//----------获取父节点索引--------------
		if (Heap::depth == 0)
		{
			cout << "节点" << index << " 不存在父节点" << endl;
			Heap::parent = -1;
		}
		else
		{
			//节点偏移量
			int offset = index - (pow(2, Heap::depth) - 1);
			//父节点偏移量
			int parent_offset = offset / 2;
			//父节点所在层头节点
			int parent_depth_head = pow(2, Heap::depth - 1) - 1;
			//得到父节点
			Heap::parent = parent_depth_head + parent_offset;
		}
		//---------------------------------------

		//-----------------获取子节点索引-----------------
		int left_node = index - (pow(2, Heap::depth) - 1);
		int right_node = pow(2, Heap::depth + 1) - 2 - index;
		Heap::left = index + right_node + 2 * left_node + 1;
		Heap::right = Heap::left + 1;
		if (Heap::left >= Heap::heap_size)
		{
			cout << "节点" << index << " 不存在左子节点" << endl;
			Heap::left = -1;
		}

		if (Heap::right >= Heap::heap_size)
		{
			cout << "节点" << index << " 不存在右子节点" << endl;
			Heap::right = -1;
		}
		//----------------------------------------------------
		return 1;
	}
	//从节点index开始维护最大堆
	int max_heapify(int index)
	{
		//迭代的时候要注意静态变量！！！
		static int largest;
		Heap::get_node_information(index);//获取当前节点对应信息
		int &l = Heap::left;
		int &r = Heap::right;
		//注意要判断节点的子节点是否存在
		if (l >= 0 && l <= Heap::heap_size&&Heap::heap_vector[l] > Heap::heap_vector[index])
			largest = l;
		else
			largest = index;
		if (r >= 0 && r <= Heap::heap_size&&Heap::heap_vector[r] > Heap::heap_vector[largest])
			largest = r;
		if (largest != index)
		{
			swap(Heap::heap_vector[index], Heap::heap_vector[largest]);
			//进行进一步迭代
			Heap::max_heapify(largest);
		}

		return 1;
	}
	//构建最大堆
	int build_max_heap()
	{
		/*
		注意此处迭代是从叶到根的方向
		由于最后一层全是叶 不存在子节点了
		所以为了降低算法开销
		直接从倒数第二层的节点开始max_heapify
		*/
		int iter_time = Heap::heap_size / 2;
		for (int i = iter_time; i >= 0; i--)
		{
			Heap::max_heapify(i);
		}
		return 1;
	}
	//堆排序
	vector<T> heap_sort()
	{
		//存下原始堆尺寸 排序过程中要改变heap_size变量 但堆尺寸其实并未改变 排序完成后将其恢复
		int origin_size = Heap::heap_size;
		vector<T> origin_heap_vector(Heap::heap_vector);//排序不应该影响heap_vector 但在排序过程中却会改变它 所以在此备份 最后恢复
		Heap::build_max_heap();
		
		for (int i = Heap::heap_size - 1; i >= 1; i--)
		{
			swap(Heap::heap_vector[0], Heap::heap_vector[i]);
			Heap::heap_size--;
			Heap::max_heapify(0);
		}
		vector<T>result(Heap::heap_vector);
		//排序时一直在减小heap_size，堆也在改变，但事实上堆尺寸并未改变 排序完成后将其恢复
		Heap::heap_size = origin_size;
		Heap::heap_vector=origin_heap_vector;
		return result;
	}
	//最大堆去掉并返回最大值 若不是最大堆 先构造最大堆
	T heap_extract_max()
	{
		if (Heap::heap_size < 1)
		{
			cout << "heap underflow" << endl;
			return -1;
		}

		Heap::build_max_heap();
		T max = Heap::heap_vector[0];
		Heap::heap_vector[0] = Heap::heap_vector[Heap::heap_size - 1];
		Heap::heap_vector.pop_back();
		//这时是真的改变了堆尺寸 不用恢复了
		Heap::heap_size--;
		Heap::max_heapify(0);
		return max;
	}
	//增大最大堆某元素 若不是最大堆 先构造最大堆
	int heap_increase_key(int index, T key)
	{
		Heap::build_max_heap();
		//获取节点信息
		Heap::get_node_information(index);
		if (key < Heap::heap_vector[index])
		{
			cout << "new key is smaller than current key" << endl;
			return -1;
		}
		Heap::heap_vector[index] = key;
		while (index > 0 && Heap::heap_vector[Heap::parent] < Heap::heap_vector[index])
		{
			swap(Heap::heap_vector[index], Heap::heap_vector[Heap::parent]);
			index = Heap::parent;
			//注意更新新节点的信息
			Heap::get_node_information(index);
		}
		return 1;
	}
	//最大堆插入元素 若不是最大堆 先构建最大堆
	int max_heap_insert(T key)
	{
		Heap::build_max_heap();
		//插入一个新元素后尺寸要加1
		Heap::heap_size++;
		//将负无穷插入到堆末 此时仍是最大堆
		Heap::heap_vector.push_back(INT_MIN);
		//用之前的increase方法将该负无穷改成（增大为）实际插入值，构建新的最大堆
		Heap::heap_increase_key(Heap::heap_size - 1, key);

		return 1;
	}

	//堆尺寸
	int heap_size;
	//当前索引，从0开始
	int index;
	//当前索引左索引
	int left;
	//当前索引右索引
	int right;
	//当前索引父索引
	int parent;
	//当前层数
	int depth;
	//堆对应的vector
	vector<T> heap_vector;
};

//第七章快速排序
/*
这里要非常注意“划分”这个词非常容易引起误导
划分一个数组，很容易把这种操作理解为把一根棍子撇成两半
但是在此处 数组元素的整个顺序都被打乱了 这根棍子被彻底分解重组了 而不是简单的划分成两半
打乱之后按一个阈值（也是一个数组元素，此处取的是最后一个元素）隔离开来
所以 应该管他叫“重组隔离”之类的更合理
*/
//返回值为阈值的新位置
template <typename T>
int partition(vector<T> &arr, int p, int r)
{
	T x = arr[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (arr[j] <= x)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[r]);
	return i + 1;
}

//快速排序 基于上一个函数
template <typename T>
int quick_sort(vector<T> &arr, int p, int r)
{
	static int q;
	if (p < r)
	{
		q = partition(arr, p, r);
		quick_sort(arr, p, q - 1);
		quick_sort(arr, q + 1, r);
	}
	return 1;
}
//生成[a,b]的随机整数
int randint(int a, int b);
//随机partition 随机取阈值，而不是最后一个了
template <typename T>
int random_partition(vector<T> &arr, int p, int r)
{
	int i = randint(p, r);
	swap(arr[r], arr[i]);
	return partition(arr, p, r);
}


//随机快速分类 基于随机partition
template <typename T>
int random_quick_sort(vector<T> &arr, int p, int r)
{
	if (p < r)
	{
		int q = random_partition(arr, p, r);
		random_quick_sort(arr, p, q - 1);
		random_quick_sort(arr, q + 1, r);
	}
	return 0;
}



