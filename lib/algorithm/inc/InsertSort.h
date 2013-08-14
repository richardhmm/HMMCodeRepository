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
 * @file InsertSort.h
 * @brief bubble sort declaration
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-13
 */
#ifndef INSERTSORT_H_
#define INSERTSORT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#define FALSE false
#define TRUE true

typedef int ISortType;

/**
 * @brief insert sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if InsertSort is ok
 */
bool InsertSort(ISortType* data, int len, bool isAscend);

#ifdef  __cplusplus
}
#endif

#endif /* INSERTSORT_H_ */
