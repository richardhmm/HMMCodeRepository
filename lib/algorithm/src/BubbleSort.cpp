/*
 Copyright (c) 2013 richard.hmm

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a coy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */
/**
 * @file BubbleSort.cpp
 * @brief bubble sort
 * @details http://www.cnblogs.com/morewindows/archive/2011/08/06/2129603.html
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-10
 */
#include <iostream>

#include "Log.h"
#include "BubbleSort.h"

static void BubbleSortAscend(BSortType a[], int n)
{
	int j, k;
	int flag;
	BSortType temp;

	flag = n;
	while (flag > 0)
	{
		k = flag;
		flag = 0;
		for (j = 1; j < k; j++)
		{
			if (a[j - 1] > a[j])
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
				flag = j;
			}
		}
	}
}

static void BubbleSortDescend(BSortType a[], int n)
{
	int j, k;
	int flag;
	BSortType temp;

	flag = n;
	while (flag > 0)
	{
		k = flag;
		flag = 0;
		for (j = 1; j < k; j++)
		{
			if (a[j - 1] < a[j])
			{
				temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;
				flag = j;
			}
		}
	}
}

/**
 * @brief bubble sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if BubbleSort is ok
 */
bool BubbleSort(BSortType data[], int len, bool isAscend)
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
		BubbleSortAscend(data, len);
	}
	else
	{
		BubbleSortDescend(data, len);
	}

	return true;
}

