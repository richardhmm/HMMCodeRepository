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
 * @file InsertSort.cpp
 * @brief insert sort
 * @details http://www.cnblogs.com/morewindows/archive/2011/08/06/2129603.html
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-10
 */
#include <iostream>

#include "Log.h"
#include "InsertSort.h"

static void InsertSortAscend(ISort_t a[], int n)
{
	ISort_t temp;
	int i, j;

	for (i = 1; i < n; i++)
	{
		if (a[i] < a[i - 1])
		{
			temp = a[i];
			for (j = i - 1; (j >= 0) && (a[j] > temp); j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = temp;
		}
	}
}

static void InsertSortDescend(ISort_t a[], int n)
{
	ISort_t temp;
	int i, j;

	for (i = 1; i < n; i++)
	{
		if (a[i] > a[i - 1])
		{
			temp = a[i];
			for (j = i - 1; (j >= 0) && (a[j] < temp); j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = temp;
		}
	}
}

/**
 * @brief insert sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if InsertSort is ok
 */
bool InsertSort(ISort_t data[], int len, bool isAscend)
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
		InsertSortAscend(data, len);
	}
	else
	{
		InsertSortDescend(data, len);
	}

	return true;
}

