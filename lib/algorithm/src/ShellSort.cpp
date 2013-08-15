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
 * @file ShellSort.cpp
 * @brief insert sort
 * @details http://www.cnblogs.com/morewindows/archive/2011/08/08/2130684.html
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-8-15
 */
#include <iostream>

#include "Log.h"
#include "ShellSort.h"

static void ShellSortAscend(ShellSortType a[], int n)
{
	ShellSortType temp;
    int i, j, gap;

    for (gap = n / 2; gap > 0; gap /= 2)
    {
           for (i = gap; i < n; i++)
           {
                  for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
                  {
                         temp = a[j];
                         a[j] = a[j + gap];
                         a[j + gap] = temp;
                  }
           }
    }
}

static void ShellSortDescend(ShellSortType a[], int n)
{
	ShellSortType temp;
    int i, j, gap;

    for (gap = n / 2; gap > 0; gap /= 2)
    {
           for (i = gap; i < n; i++)
           {
                  for (j = i - gap; j >= 0 && a[j] < a[j + gap]; j -= gap)
                  {
                         temp = a[j];
                         a[j] = a[j + gap];
                         a[j + gap] = temp;
                  }
           }
    }
}

/**
 * @brief insert sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if ShellSort is ok
 */
bool ShellSort(ShellSortType data[], int len, bool isAscend)
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
		ShellSortAscend(data, len);
	}
	else
	{
		ShellSortDescend(data, len);
	}

	return true;
}

