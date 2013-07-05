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
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-4
 */
#include <iostream>

#include "Log.h"
#include "QuickSort.h"

static typeQuickSort Division(typeQuickSort* data, int left,
		int right, bool isAscend)
{
    // 选择一个基准元素  select a data for base
    typeQuickSort base = data[left];

	if (isAscend) { // ascend sort
	    while (left < right){
	    	// 从数组的右端开始向前查找，一直找到比base小的数值为止（包括base同等数）
	        while ((left < right) && (data[right] >= base)){
	        	right--;
	        }

	        // 最终找到了比base小的元素，要做的事情就是将此元素放到base的位置
	        data[left] = data[right];

	        // 从数组的左端开始向前查找，一直找到比base大的数值为止（包括base同等数）
	        while ((left < right) && (data[left] <= base)){
	        	left++;
	        }

	        // 最终找到了比base大的元素，要做的事情就是将此元素放到最后的位置
	        data[right] = data[left];

	        // 最后把base放到left的位置
	        data[left] = base;

	        // 最终，我们发现left位置的左侧数值部分比left小，left位置右侧数值比left大
	        return left;
	    }
	} else { // descend sort
	    while (left < right){
	    	// 从数组的右端开始向前查找，一直找到比base大的数值为止（包括base同等数）
	        while ((left < right) && (data[right] <= base)){
	        	right--;
	        }

	        // 最终找到了比base大的元素，要做的事情就是将此元素放到base的位置
	        data[left] = data[right];

	        // 从数组的左端开始向前查找，一直找到比base小的数值为止（包括base同等数）
	        while ((left < right) && (data[left] >= base)){
	        	left++;
	        }

	        // 最终找到了比base小的元素，要做的事情就是将此元素放到最后的位置
	        data[right] = data[left];

	        // 最后把base放到left的位置
	        data[left] = base;

	        // 最终，我们发现left位置的左侧数值部分比left大，left位置右侧数值比left小
	        return left;
	    }
	}

}

static void QuickSort_(typeQuickSort* data, int left,
		int right, bool isAscend)
{
    // 对数组进行分割，取出下次分割的基准标号
	int i = Division(data, left, right, isAscend);

    // 对“基准标号”左侧的一组数值进行递归切割，以便将这些数据完整的排序
    if (i - 1 > left)   //大于号右面是整数1，左边是变量l
        QuickSort_(data, left, i - 1, isAscend);

    // 对“基准标号”右侧的一组数值进行递归切割，以便将这些数据完整的排序
    if (right > i + 1)
        QuickSort_(data, i + 1, right, isAscend);
}

/**
 * @brief quick sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if QuickSort is ok
 */
bool QuickSort(typeQuickSort* data, int len, bool isAscend)
{
    if (NULL == data){
    	LOG_FATAL("NULL == data");
    	return false;
    }
    if (len <= 0){
    	LOG_FATAL("len <= 0");
    	return false;
    }

    if (1 == len){
    	LOG_INFO("len == 1, sort ok");
    	return true;
    }

    QuickSort_(data, 0, len - 1, isAscend);
    return true;
}
