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
 * @file Test_SelectSort.cpp
 * @brief unit test for Insert sort
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-13
 */
#include "gtest/gtest.h"
#include "Log.h"
#include "SelectSort.h"

using namespace std;

int main(int argc, char* argv[])
{
	InitLogger();
	testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(SelectSort, CheckParam)
{
	SSort_t data[5] = {20, 40, 50, 10, 60};

	// ok
	ASSERT_TRUE(SelectSort(data, 5, true));

	// check data param
	ASSERT_FALSE(SelectSort(NULL, 5, true));

	// check len param
	ASSERT_FALSE(SelectSort(data, 0, true));
	ASSERT_TRUE(SelectSort(data, 1, true));
	ASSERT_FALSE(SelectSort(data, -1, true));

	// check isAscend param
	ASSERT_TRUE(SelectSort(data, 5, false));
}

TEST(SelectSort, CheckData)
{
	SSort_t data[5] = {20, 40, 50, 10, 60};

	// check data ok
	ASSERT_TRUE(SelectSort(data, 5, true));
	ASSERT_EQ(10, data[0]);
	ASSERT_EQ(20, data[1]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[3]);
	ASSERT_EQ(60, data[4]);
}

TEST(SelectSort, CheckData1)
{
	SSort_t data[5] = {20, 40, 50, 20, 60};

	// check data ok
	ASSERT_TRUE(SelectSort(data, 5, true));
	ASSERT_EQ(20, data[0]);
	ASSERT_EQ(20, data[1]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[3]);
	ASSERT_EQ(60, data[4]);
}

TEST(SelectSort, CheckData2)
{
	SSort_t data[6] = {20, 40, 50, 20, 60, 20};

	// check data ok
	ASSERT_TRUE(SelectSort(data, 6, true));
	ASSERT_EQ(20, data[0]);
	ASSERT_EQ(20, data[1]);
	ASSERT_EQ(20, data[2]);
	ASSERT_EQ(40, data[3]);
	ASSERT_EQ(50, data[4]);
	ASSERT_EQ(60, data[5]);
}

TEST(SelectSort, CheckData3)
{
	SSort_t data[5] = {20, 40, 50, 10, 60};

	// check data ok
	ASSERT_TRUE(SelectSort(data, 5, false));
	ASSERT_EQ(10, data[4]);
	ASSERT_EQ(20, data[3]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[1]);
	ASSERT_EQ(60, data[0]);
}

TEST(SelectSort, CheckData4)
{
	SSort_t data[5] = {20, 40, 50, 20, 60};

	// check data ok
	ASSERT_TRUE(SelectSort(data, 5, false));
	ASSERT_EQ(20, data[4]);
	ASSERT_EQ(20, data[3]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[1]);
	ASSERT_EQ(60, data[0]);
}

TEST(SelectSort, CheckData5)
{
	SSort_t data[6] = {20, 40, 50, 20, 60, 20};

	// check data ok
	ASSERT_TRUE(SelectSort(data, 6, false));
	ASSERT_EQ(20, data[5]);
	ASSERT_EQ(20, data[4]);
	ASSERT_EQ(20, data[3]);
	ASSERT_EQ(40, data[2]);
	ASSERT_EQ(50, data[1]);
	ASSERT_EQ(60, data[0]);
}
