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
 * @file Test_BubbleSort.cpp
 * @brief unit test for bubble sort
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-10
 */
#include "gtest/gtest.h"
#include "Log.h"
#include "BubbleSort.h"

using namespace std;

int main(int argc, char* argv[])
{
	InitLogger();
	testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(BubbleSort, CheckParam)
{
	BSort_t data[5] = {20, 40, 50, 10, 60};

	// ok
	ASSERT_TRUE(BubbleSort(data, 5, true));

	// check data param
	ASSERT_FALSE(BubbleSort(NULL, 5, true));

	// check len param
	ASSERT_FALSE(BubbleSort(data, 0, true));
	ASSERT_TRUE(BubbleSort(data, 1, true));
	ASSERT_FALSE(BubbleSort(data, -1, true));

	// check isAscend param
	ASSERT_TRUE(BubbleSort(data, 5, false));
}

TEST(BubbleSort, CheckData)
{
	BSort_t data[5] = {20, 40, 50, 10, 60};

	// check data ok
	ASSERT_TRUE(BubbleSort(data, 5, true));
	ASSERT_EQ(10, data[0]);
	ASSERT_EQ(20, data[1]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[3]);
	ASSERT_EQ(60, data[4]);
}

TEST(BubbleSort, CheckData1)
{
	BSort_t data[5] = {20, 40, 50, 20, 60};

	// check data ok
	ASSERT_TRUE(BubbleSort(data, 5, true));
	ASSERT_EQ(20, data[0]);
	ASSERT_EQ(20, data[1]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[3]);
	ASSERT_EQ(60, data[4]);
}

TEST(BubbleSort, CheckData2)
{
	BSort_t data[6] = {20, 40, 50, 20, 60, 20};

	// check data ok
	ASSERT_TRUE(BubbleSort(data, 6, true));
	ASSERT_EQ(20, data[0]);
	ASSERT_EQ(20, data[1]);
	ASSERT_EQ(20, data[2]);
	ASSERT_EQ(40, data[3]);
	ASSERT_EQ(50, data[4]);
	ASSERT_EQ(60, data[5]);
}

TEST(BubbleSort, CheckData3)
{
	BSort_t data[5] = {20, 40, 50, 10, 60};

	// check data ok
	ASSERT_TRUE(BubbleSort(data, 5, false));
	ASSERT_EQ(10, data[4]);
	ASSERT_EQ(20, data[3]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[1]);
	ASSERT_EQ(60, data[0]);
}

TEST(BubbleSort, CheckData4)
{
	BSort_t data[5] = {20, 40, 50, 20, 60};

	// check data ok
	ASSERT_TRUE(BubbleSort(data, 5, false));
	ASSERT_EQ(20, data[4]);
	ASSERT_EQ(20, data[3]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[1]);
	ASSERT_EQ(60, data[0]);
}

TEST(BubbleSort, CheckData5)
{
	BSort_t data[6] = {20, 40, 50, 20, 60, 20};

	// check data ok
	ASSERT_TRUE(BubbleSort(data, 6, false));
	ASSERT_EQ(20, data[5]);
	ASSERT_EQ(20, data[4]);
	ASSERT_EQ(20, data[3]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[1]);
	ASSERT_EQ(60, data[0]);
}
