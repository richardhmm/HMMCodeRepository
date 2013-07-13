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
 * @file main.cpp
 * @brief example for algorithm
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-8
 */

#include<stdio.h>

#include "Log.h"
#include "QuickSort.h"
#include "BubbleSort.h"
#include "InsertSort.h"

using namespace std;

static void qsort()
{
	LOG_INFO("in qsort()");
	int len = 0;

    // 10 random number to sort
	len = 10;
    QSort_t data1[len];
    printf("\n\n===================1===================\n");
    for (int i = 0; i < len; i++){
    	data1[i] = rand()%9 + 1;
    	printf("%3d  ", data1[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }
    LOG_INFO("1. sort start");
    QuickSort(data1, len, true);
    LOG_INFO("1. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d  ", data1[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }

    // 100 random number to sort
    len = 100;
    QSort_t data2[len];
    printf("\n\n===================2===================\n");
    for (int i = 0; i < len; i++){
    	data2[i] = rand()%9 + 1;
    	printf("%3d  ", data2[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }
    LOG_INFO("2. sort start");
    QuickSort(data2, len, true);
    LOG_INFO("2. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d  ", data2[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }

    // 1000 random number to sort
    len = 1000;
    QSort_t data3[len];
    printf("\n\n===================3===================\n");
    for (int i = 0; i < len; i++){
    	data3[i] = rand()%8 + 1;
    	printf("%3d ", data3[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
    LOG_INFO("3. sort start");
    QuickSort(data3, len, true);
    LOG_INFO("3. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d ", data3[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }

    // 1000 random number to sort
    len = 1000;
    QSort_t data4[len];
    printf("\n\n===================4===================\n");
    for (int i = 0; i < len; i++){
    	data4[i] = rand()%8 + 1;
    	printf("%3d ", data4[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
    LOG_INFO("4. sort start");
    QuickSort(data4, len, false);
    LOG_INFO("4. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d ", data4[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
}

static void bsort()
{
	LOG_INFO("in bsort()");

	int len = 0;

    // 10 random number to sort
	len = 10;
    BSort_t data1[len];
    printf("\n\n===================1===================\n");
    for (int i = 0; i < len; i++){
    	data1[i] = rand()%9 + 1;
    	printf("%3d  ", data1[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }
    LOG_INFO("1. sort start");
    BubbleSort(data1, len, true);
    LOG_INFO("1. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d  ", data1[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }

    // 100 random number to sort
    len = 100;
    BSort_t data2[len];
    printf("\n\n===================2===================\n");
    for (int i = 0; i < len; i++){
    	data2[i] = rand()%9 + 1;
    	printf("%3d  ", data2[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }
    LOG_INFO("2. sort start");
    BubbleSort(data2, len, true);
    LOG_INFO("2. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d  ", data2[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }

    // 1000 random number to sort
    len = 1000;
    BSort_t data3[len];
    printf("\n\n===================3===================\n");
    for (int i = 0; i < len; i++){
    	data3[i] = rand()%8 + 1;
    	printf("%3d ", data3[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
    LOG_INFO("3. sort start");
    BubbleSort(data3, len, true);
    LOG_INFO("3. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d ", data3[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }

    // 1000 random number to sort
    len = 1000;
    BSort_t data4[len];
    printf("\n\n===================4===================\n");
    for (int i = 0; i < len; i++){
    	data4[i] = rand()%8 + 1;
    	printf("%3d ", data4[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
    LOG_INFO("4. sort start");
    BubbleSort(data4, len, false);
    LOG_INFO("4. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d ", data4[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
}

static void isort()
{
	LOG_INFO("in isort()");

	int len = 0;

    // 10 random number to sort
	len = 10;
    ISort_t data1[len];
    printf("\n\n===================1===================\n");
    for (int i = 0; i < len; i++){
    	data1[i] = rand()%9 + 1;
    	printf("%3d  ", data1[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }
    LOG_INFO("1. sort start");
    InsertSort(data1, len, true);
    LOG_INFO("1. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d  ", data1[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }

    // 100 random number to sort
    len = 100;
    ISort_t data2[len];
    printf("\n\n===================2===================\n");
    for (int i = 0; i < len; i++){
    	data2[i] = rand()%9 + 1;
    	printf("%3d  ", data2[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }
    LOG_INFO("2. sort start");
    InsertSort(data2, len, true);
    LOG_INFO("2. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d  ", data2[i]);
    	if ((i + 1) % 5 == 0)
    		printf("\n");
    }

    // 1000 random number to sort
    len = 1000;
    ISort_t data3[len];
    printf("\n\n===================3===================\n");
    for (int i = 0; i < len; i++){
    	data3[i] = rand()%8 + 1;
    	printf("%3d ", data3[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
    LOG_INFO("3. sort start");
    InsertSort(data3, len, true);
    LOG_INFO("3. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d ", data3[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }

    // 1000 random number to sort
    len = 1000;
    ISort_t data4[len];
    printf("\n\n===================4===================\n");
    for (int i = 0; i < len; i++){
    	data4[i] = rand()%8 + 1;
    	printf("%3d ", data4[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
    LOG_INFO("4. sort start");
    InsertSort(data4, len, false);
    LOG_INFO("4. sort end");
    for (int i = 0; i < len; i++){
    	printf("%3d ", data4[i]);
    	if ((i + 1) % 20 == 0)
    		printf("\n");
    }
}

int main(int argc, char* argv[])
{
	InitLogger();

//	qsort();
//	bsort();
	isort();

    return 0;
}

