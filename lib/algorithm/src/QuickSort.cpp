/*
 Copyright (c) 2013 richard.hmm

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
/**
 * @file QuickSort.cpp
 * @brief quick sort
 * @details http://www.cnblogs.com/huangxincheng/archive/2011/11/14/2249046.html
 * 			http://www.cnblogs.com/morewindows/archive/2011/08/13/2137415.html
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-4
 */
#include <iostream>

#include "Log.h"
#include "QuickSort.h"

static void QuickSortAscend(QSort_t* s, int l, int r)
{
	if (l < r)
	{
		//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
		int i = l, j = r;
		QSort_t x = s[l];

		while (i < j)
		{
			while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
				j--;

			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;

			if (i < j)
				s[j--] = s[i];
		}

		s[i] = x;
		if (l < i - 1)
			QuickSortAscend(s, l, i - 1); // 递归调用

		if (i + 1 < r)
			QuickSortAscend(s, i + 1, r);
	}
}

static void QuickSortDescend(QSort_t* s, int l, int r)
{
	if (l < r)
	{
		//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
		int i = l, j = r;
		QSort_t x = s[l];

		while (i < j)
		{
			while (i < j && s[j] < x) // 从右向左找第一个大于x的数
				j--;

			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] >= x) // 从左向右找第一个小于等于x的数
				i++;

			if (i < j)
				s[j--] = s[i];
		}

		s[i] = x;
		if (l < i - 1)
			QuickSortDescend(s, l, i - 1); // 递归调用

		if (i + 1 < r)
			QuickSortDescend(s, i + 1, r);
	}
}

/**
 * @brief quick sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if QuickSort is ok
 */
bool QuickSort(QSort_t* data, int len, bool isAscend)
{
	if (NULL == data)
	{
		LOG_FATAL("NULL == data");
		return false;
	}
	if (len <= 0)
	{
		LOG_FATAL("len <= 0");
		return false;
	}

	if (1 == len)
	{
		LOG_INFO("len == 1, sort ok");
		return true;
	}

	if (isAscend)
	{
		QuickSortAscend(data, 0, len - 1);
	}
	else
	{
		QuickSortDescend(data, 0, len - 1);
	}

	return true;
}

