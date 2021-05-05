/**
 * \file CAnimChannelAngleTest.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "CppUnitTest.h"
#include "AnimChannelAngle.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CAnimChannelAngleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCAnimChannelAngleNameGetterAndSetter)
		{
			CAnimChannel channel;
			channel.SetName(L"Harold");
			Assert::AreEqual(channel.GetName(), std::wstring(L"Harold"));
		}

	};
}