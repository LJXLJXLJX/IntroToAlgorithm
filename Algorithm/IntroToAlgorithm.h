#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <limits>
#include <random>


using namespace std;




//2.1-1��2 insertion - sort mode 0Ϊ����
template <typename T>
vector<T> insertion_sort(vector<T> &arr, int mode = 0)
{


	int len = arr.size();
	for (int i = 0; i < len; i++)
	{
		int origin_i = i;
		auto temp = arr[i];
		if (mode == 0)//�ǽ���
			while (i > 0 && temp < arr[i - 1])
				i--;
		if (mode == 1)//������
			while (i > 0 && temp > arr[i - 1])
				i--;
		arr.erase(begin(arr) + origin_i);
		arr.insert(begin(arr) + i, temp);
	}
	return arr;
}


//2.1-3 �������⣬������A���ҵ�v�������±ꡣ��������v������-1
template <typename T>
vector<int> find_out(vector<T> A, T v)
{
	int len = A.size();//����A����
	vector<int> result;//���ص��±�i
	for (int i = 0; i < len; i++)
	{
		if (v == A[i])
			result.push_back(i);
	}
	if (result.empty())
	{
		cout << "�����в�����v" << endl;
		return { -1 };
	}
	else
		return result;
}

//2.1-4��������ӣ�������������������ʾ
vector<int> binary_add(vector<int> a, vector<int> b);


//2.3-1��2�鲢����
template <typename T>
vector<T> merge_two(vector<T> vec1, vector<T> vec2)	//�������Ѿ��ź����ʸ���鲢
{
	vector<T> reverse_result;	//��ת�Ľ��
	vector<T> result;	//������������vectorֻ����β�������� ��merge�õ��Ľ��reverse_result��ʵ�Ƿ�ת�� �ٷ�תһ�μ��ɵõ���ȷ�Ľ����
	while (vec1.size() > 0 || vec2.size() > 0)	//û���ڱ��� �ȴ�С�����
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

		else if (vec1.size() == 0)	//vec1�����ڱ��� ��2
		{
			reverse_result.push_back(vec2.back());
			vec2.pop_back();
		}
		else if (vec2.size() == 0)	//vec2�����ڱ��� ��1
		{
			reverse_result.push_back(vec1.back());
			vec1.pop_back();
		}
		else
			cout << "something wrong!!!" << endl;

	}
	//���������ת���ɵõ���ȷ���
	while (reverse_result.size() != 0)
	{
		result.push_back(reverse_result.back());
		reverse_result.pop_back();
	}

	return result;
}

template <typename T>
vector<T> merge(vector<T>arr)	//�鲢 ��������һ������
{
	vector<vector<T>> vec_container;//����һ�����ɣ�����ʸ����ʸ��

	for (auto i : arr)//��ÿ��ֵװ��ÿ����ʸ����
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

//2.3-5 �������еĶ��ַ�����
template <typename T>
vector<int> bisection_find_out(vector<T> A, T v)
{
	vector<T> section;	//���ն�
	int head = 0;		//��ͷ����
	int tail = A.size() - 1;	//��β����
	int offset = A.size() / 2 + A.size() % 2;	//�е�ƫ��
	int center = head + offset - 1;		//�е�
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

//4.1-2 ���������������� ����ֵΪͷβ�����Լ�������Ԫ���ܺͣ������ڶ����������� �ҵ���ҵ��Ǹ���
template <typename T>
vector<T> brainless_find_max_subarray(vector<T> arr)
{
	int sum = 0;	//Ԫ�غ�
	T max_sum = 0;	//���Ԫ�غ�
	int max_subarray_head = 0;	//���������ͷ
	int max_subarray_tail = 0;	//���������β
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

//4.1-3 ���������ݹ鷨
template <typename T>
vector<T> find_max_crossing_subarray(vector<T> arr, int low, int mid, int high)	//	�ҵ����е�����������
{
	T left_sum = 0;
	T right_sum = 0;
	int max_left;
	int max_right;
	T sum;
	vector<T> left_vec(arr.begin() + low, arr.begin() + mid + 1);
	vector<T> right_vec(arr.begin() + mid + 1, arr.begin() + high + 1);
	max_left = brainless_find_max_subarray(left_vec)[0] + low;	//������������ͷ
	vector<T> left_max_vec(left_vec.begin() + (max_left - low), left_vec.end());	//���е��������������
	for (auto i : left_max_vec)	//���е��������������Ԫ��֮��
		left_sum += i;
	max_right = brainless_find_max_subarray(right_vec)[1] + mid + 1;
	vector<T> right_max_vec(right_vec.begin(), right_vec.begin() + (max_right - mid));	//���е��������������
	for (auto i : right_max_vec)//���е㿪ʼ�Ұ����������֮��
		right_sum += i;
	sum = right_sum + left_sum;
	vector<T> result = { T(max_left) ,T(max_right) ,sum };
	return result;
}

template <typename T>
vector<T> find_max_subarray(vector<T> arr, int low, int high)	//�ݹ������������
{
	//�ݹ�����Ҫ�þ�̬�����������ظ���ʼ��
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

//4.2 ����˷�
//square matrix multiply
template <typename T>
vector<vector<T>> matrix_multiply(vector<vector<T>> A, vector<vector<T>> B)
{
	vector<vector<T>> error_flag = { { 0 } };
	//----�жϾ���A�Ƿ�Ϊ�淶�ľ���------
	int m = A.size();//����
	int n = A[0].size();//��һ�е�Ԫ���� ÿһ��Ӧ��һ��
	for (int i = 1; i < m; i++)
	{
		if (A[i].size() != n)
		{
			cout << "�������A���淶" << endl;
			return error_flag;
		}
	}
	//----------------------------
	//----�жϾ���B�Ƿ�Ϊ�淶�ľ���-----
	int a = B.size();
	int b = B[0].size();
	for (int i = 1; i < a; i++)
	{
		if (A[i].size() != b)
		{
			cout << "�������B���淶" << endl;
			return error_flag;
		}
	}
	//---------------------------------
	//----�ж�A,B�ܷ�������˷�--------
	if (n != a)
	{
		cout << "A,B����������˷�" << endl;
		return error_flag;
	}
	//----------------------------

	//---------������----------
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
//����ӷ�
template <typename T>
vector<vector<T>> matrix_add(vector<vector<T>> A, vector<vector<T>> B)
{
	vector<vector<T>> error_flag = { { 0 } };
	//------�ж�A,B�Ƿ�Ϊ�淶�ľ���--------
	int m = A.size(), n = A[0].size(), a = B.size(), b = B[0].size();
	if (m != a || n != b)
	{
		cout << "A��B������һ��" << endl;
		return error_flag;
	}
	for (auto i : A)
	{
		if (i.size() != n)
		{
			cout << "A���ǹ淶�ľ���" << endl;
			return error_flag;
		}
	}
	for (auto i : B)
	{
		if (i.size() != b)
		{
			cout << "B���ǹ淶�ľ���" << endl;
			return error_flag;
		}
	}
	//----------------------------------
	//------------����---------
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
//����ķ��γ˷����ֿ�˷�����������Ϊ2^n
template <typename T>
vector<vector<T>> square_matrix_multiply_recursive(vector<vector<T>> A, vector<vector<T>> B)
{
	int n = A.size();
	vector<vector<T>> error_flag = { { 0 } };
	vector<T> initial_row(n, 0);
	vector<vector<T>> C(n, initial_row);
	//----�жϾ���A,B�Ƿ�Ϊ2^n�׷���-----
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
				cout << "����������������������2^n" << endl;
				return error_flag;
			}
		}
		if (A.size() != B.size())
		{
			cout << "A,B������ͬ" << endl;
			return error_flag;
		}
		//----------------------------------
		//-------�ж�A,B�Ƿ�Ϊ�淶�ķ���-----
		for (auto i : A)
		{
			if (i.size() != n)
			{
				cout << "A���ǹ淶�ķ���" << endl;
				return error_flag;
			}
		}
		for (auto i : B)
		{
			if (i.size() != n)
			{
				cout << "B���ǹ淶�ķ���" << endl;
				return error_flag;
			}
		}

		//-----������---------
		//----�Ӿ���ĸ�ֵ�����ƣ�----
		/*�㷨���۴˴������ƿ��Ӿ���Ĵ����븳ֵ��ֱ����ԭʼ������±���������˵������������
		�Լ�������ԣ�C++ STL�£�������û�������ľ����������͡�
		��νֱ�����±����㣬�����Ʋ����¾���(vector)�Ĵ����븳ֵ�����ƣ�*/
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
		//---------�ݹ�������Ӿ���---------------
		C11 = matrix_add(square_matrix_multiply_recursive(A11, B11), square_matrix_multiply_recursive(A12, B21));
		C12 = matrix_add(square_matrix_multiply_recursive(A11, B12), square_matrix_multiply_recursive(A12, B22));
		C21 = matrix_add(square_matrix_multiply_recursive(A21, B11), square_matrix_multiply_recursive(A22, B21));
		C22 = matrix_add(square_matrix_multiply_recursive(A21, B12), square_matrix_multiply_recursive(A22, B22));
		//--------------------------------
		//-----�ϲ��Ӿ���------------
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


//������ �� 
/*
ֻʵ������������㷨
��С���޷Ǿ����հ���·���ĸ�����С��
����Ū�ˣ��Ժ�����Ҫ�ٲ���
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
	//��ȡ��ǰ�ڵ㣨��������Ӧ����Ϣ��������� �ӽڵ㣩
	int get_node_information(int index)
	{
		Heap::depth = 0;
		if (index < 0 || index >= heap_size)
		{
			cout << "�����������󣬲��ڵ�ǰ�ѷ�Χ��" << endl;
			return -1;
		}
		//---------��ȡ�����£���ǰ�ڵ��������---------------
		/*
		��Ⱥ��������Ǵ��㿪ʼ����
		ÿ���ͷβ�ڵ�ֱ��� 2^depth-1 �� 2*(2^depth-1)
		*/
		while (1)
		{
			if (index >= pow(2, Heap::depth) - 1 && index <= pow(2, Heap::depth + 1) - 2)
				break;
			Heap::depth++;
		}
		//-----------------------------------------

		//----------��ȡ���ڵ�����--------------
		if (Heap::depth == 0)
		{
			cout << "�ڵ�" << index << " �����ڸ��ڵ�" << endl;
			Heap::parent = -1;
		}
		else
		{
			//�ڵ�ƫ����
			int offset = index - (pow(2, Heap::depth) - 1);
			//���ڵ�ƫ����
			int parent_offset = offset / 2;
			//���ڵ����ڲ�ͷ�ڵ�
			int parent_depth_head = pow(2, Heap::depth - 1) - 1;
			//�õ����ڵ�
			Heap::parent = parent_depth_head + parent_offset;
		}
		//---------------------------------------

		//-----------------��ȡ�ӽڵ�����-----------------
		int left_node = index - (pow(2, Heap::depth) - 1);
		int right_node = pow(2, Heap::depth + 1) - 2 - index;
		Heap::left = index + right_node + 2 * left_node + 1;
		Heap::right = Heap::left + 1;
		if (Heap::left >= Heap::heap_size)
		{
			cout << "�ڵ�" << index << " ���������ӽڵ�" << endl;
			Heap::left = -1;
		}

		if (Heap::right >= Heap::heap_size)
		{
			cout << "�ڵ�" << index << " ���������ӽڵ�" << endl;
			Heap::right = -1;
		}
		//----------------------------------------------------
		return 1;
	}
	//�ӽڵ�index��ʼά������
	int max_heapify(int index)
	{
		//������ʱ��Ҫע�⾲̬����������
		static int largest;
		Heap::get_node_information(index);//��ȡ��ǰ�ڵ��Ӧ��Ϣ
		int &l = Heap::left;
		int &r = Heap::right;
		//ע��Ҫ�жϽڵ���ӽڵ��Ƿ����
		if (l >= 0 && l <= Heap::heap_size&&Heap::heap_vector[l] > Heap::heap_vector[index])
			largest = l;
		else
			largest = index;
		if (r >= 0 && r <= Heap::heap_size&&Heap::heap_vector[r] > Heap::heap_vector[largest])
			largest = r;
		if (largest != index)
		{
			swap(Heap::heap_vector[index], Heap::heap_vector[largest]);
			//���н�һ������
			Heap::max_heapify(largest);
		}

		return 1;
	}
	//��������
	int build_max_heap()
	{
		/*
		ע��˴������Ǵ�Ҷ�����ķ���
		�������һ��ȫ��Ҷ �������ӽڵ���
		����Ϊ�˽����㷨����
		ֱ�Ӵӵ����ڶ���Ľڵ㿪ʼmax_heapify
		*/
		int iter_time = Heap::heap_size / 2;
		for (int i = iter_time; i >= 0; i--)
		{
			Heap::max_heapify(i);
		}
		return 1;
	}
	//������
	vector<T> heap_sort()
	{
		//����ԭʼ�ѳߴ� ���������Ҫ�ı�heap_size���� ���ѳߴ���ʵ��δ�ı� ������ɺ���ָ�
		int origin_size = Heap::heap_size;
		vector<T> origin_heap_vector(Heap::heap_vector);//����Ӧ��Ӱ��heap_vector �������������ȴ��ı��� �����ڴ˱��� ���ָ�
		Heap::build_max_heap();
		
		for (int i = Heap::heap_size - 1; i >= 1; i--)
		{
			swap(Heap::heap_vector[0], Heap::heap_vector[i]);
			Heap::heap_size--;
			Heap::max_heapify(0);
		}
		vector<T>result(Heap::heap_vector);
		//����ʱһֱ�ڼ�Сheap_size����Ҳ�ڸı䣬����ʵ�϶ѳߴ粢δ�ı� ������ɺ���ָ�
		Heap::heap_size = origin_size;
		Heap::heap_vector=origin_heap_vector;
		return result;
	}
	//����ȥ�����������ֵ ���������� �ȹ�������
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
		//��ʱ����ĸı��˶ѳߴ� ���ûָ���
		Heap::heap_size--;
		Heap::max_heapify(0);
		return max;
	}
	//��������ĳԪ�� ���������� �ȹ�������
	int heap_increase_key(int index, T key)
	{
		Heap::build_max_heap();
		//��ȡ�ڵ���Ϣ
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
			//ע������½ڵ����Ϣ
			Heap::get_node_information(index);
		}
		return 1;
	}
	//���Ѳ���Ԫ�� ���������� �ȹ�������
	int max_heap_insert(T key)
	{
		Heap::build_max_heap();
		//����һ����Ԫ�غ�ߴ�Ҫ��1
		Heap::heap_size++;
		//����������뵽��ĩ ��ʱ��������
		Heap::heap_vector.push_back(INT_MIN);
		//��֮ǰ��increase�������ø�����ĳɣ�����Ϊ��ʵ�ʲ���ֵ�������µ�����
		Heap::heap_increase_key(Heap::heap_size - 1, key);

		return 1;
	}

	//�ѳߴ�
	int heap_size;
	//��ǰ��������0��ʼ
	int index;
	//��ǰ����������
	int left;
	//��ǰ����������
	int right;
	//��ǰ����������
	int parent;
	//��ǰ����
	int depth;
	//�Ѷ�Ӧ��vector
	vector<T> heap_vector;
};

//�����¿�������
/*
����Ҫ�ǳ�ע�⡰���֡�����ʷǳ�����������
����һ�����飬�����װ����ֲ������Ϊ��һ������Ʋ������
�����ڴ˴� ����Ԫ�ص�����˳�򶼱������� ������ӱ����׷ֽ������� �����Ǽ򵥵Ļ��ֳ�����
����֮��һ����ֵ��Ҳ��һ������Ԫ�أ��˴�ȡ�������һ��Ԫ�أ����뿪��
���� Ӧ�ù����С�������롱֮��ĸ�����
*/
//����ֵΪ��ֵ����λ��
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

//�������� ������һ������
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
//����[a,b]���������
int randint(int a, int b);
//���partition ���ȡ��ֵ�����������һ����
template <typename T>
int random_partition(vector<T> &arr, int p, int r)
{
	int i = randint(p, r);
	swap(arr[r], arr[i]);
	return partition(arr, p, r);
}


//������ٷ��� �������partition
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



