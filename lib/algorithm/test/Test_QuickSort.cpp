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
 * @file Test_QuickSort.cpp
 * @brief unit test for quick sort
 * @details
 * @version V1.0.0
 * @author Richard.hmm
 * @date 2013-7-4
 */
#include "gtest/gtest.h"
#include "Log.h"
#include "QuickSort.h"

using namespace std;

//TEST(QuickSort, CheckParam)
//{
//}

int main(int argc, char* argv[])
{
	InitLogger();
	testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
