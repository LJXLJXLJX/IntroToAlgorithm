#pragma once

#include "IntroToAlgorithm.h"



vector<int> binary_add(vector<int> a, vector<int> b)
{
	int len;//二进制数长度（位数）
	int len_dif = a.size() - b.size();
	len_dif = abs(len_dif);
	if (len_dif >= 0)
	{
		len = a.size();
		for (int i = 0; i < len_dif; i++)
		{
			b.insert(b.begin(), 0);
		}
	}
	else
	{
		len = b.size();
		for (int i = 0; i < len_dif; i++)
		{
			a.insert(a.begin(), 0);
		}
	}
	vector<int> result(len + 1);
	int carry = 0;//进位
	int sum;//每一位的和
	for (int i = len - 1; i >= 0; i--)
	{
		sum = a[i] + b[i] + carry;
		result[i + 1] = sum % 2;
		if (sum > 1)
			carry = 1;
		else
			carry = 0;
	}
	result[0] = carry;
	return result;
}

int randint(int a, int b)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(a, b);
	return dis(gen);
}


