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
 * @file ShellSort.h
 * @brief sort declaration
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-8-15
 */
#ifndef SHELLSORT_H_
#define SHELLSORT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#define FALSE false
#define TRUE true

typedef int ShellSortType;

/**
 * @brief insert sort
 * @param data input data pointer.
 * @param len input data length.
 * @param isAscend true: ascend sort; false: descend sort.
 * @return TRUE if ShellSort is ok
 */
bool ShellSort(ShellSortType* data, int len, bool isAscend);

#ifdef  __cplusplus
}
#endif

#endif /* SHELLSORT_H_ */
