/**
 * \file CActorTest.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "CppUnitTest.h"
#include "Actor.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

namespace Testing
{
	TEST_CLASS(CActorTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCActorConstructorAndNameGetter)
		{
			CActor actor(L"Harold");
			Assert::AreEqual(std::wstring(L"Harold"), actor.GetName());
		}

		TEST_METHOD(TestCActorEnabled)
		{
			CActor actor(L"Harold");

			// default enabled 
			Assert::IsTrue(actor.IsEnabled());

			// setter and getter
			actor.SetEnabled(false);
			Assert::IsFalse(actor.IsEnabled());
		}

		TEST_METHOD(TestCActorClickable)
		{
			CActor actor(L"Harold");

			// default clickable
			Assert::IsTrue(actor.IsClickable());

			// getter and setter
			actor.SetClickable(false);
			Assert::IsFalse(actor.IsClickable());
		}

		TEST_METHOD(TestCActorPosition)
		{
			CActor actor(L"Harold");

			// default position
			Assert::AreEqual(0, actor.GetPosition().X);
			Assert::AreEqual(0, actor.GetPosition().Y);

			// Setter and Getter
			Gdiplus::Point position = Gdiplus::Point(1, 2);
			actor.SetPosition(position);

			Assert::AreEqual(1, actor.GetPosition().X);
			Assert::AreEqual(2, actor.GetPosition().Y);
		}
	};
}