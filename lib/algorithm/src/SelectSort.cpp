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
 * @file SelectSort.cpp
 * @brief select sort
 * @details http://www.cnblogs.com/morewindows/archive/2011/08/06/2129603.html
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-10
 */
#include <iostream>

#include "Log.h"
#include "SelectSort.h"

static void Swap(SSort_t& a, SSort_t& b)
{
	SSort_t temp = a;
	a = b;
	b = temp;
}

static void SelectSortAscend(SSort_t a[], int n)
{
	int i, j;
	int nMin = 0;

	for (i = 0; i < n; i++)
	{
		nMin = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < a[nMin])
			{
				nMin = j;
			}
		}
		Swap(a[i], a[nMin]);
	}
}

static void SelectSortDescend(SSort_t a[], int n)
{
	int i, j;
	int nMax = 0;

	for (i = 0; i < n; i++)
	{
		nMax = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] > a[nMax])
			{
				nMax = j;
			}
		}
		Swap(a[i], a[nMax]);
	}
}

/**
 * @brief select sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if SelectSort is ok
 */
bool SelectSort(SSort_t data[], int len, bool isAscend)
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
		SelectSortAscend(data, len);
	}
	else
	{
		SelectSortDescend(data, len);
	}

	return true;
}

