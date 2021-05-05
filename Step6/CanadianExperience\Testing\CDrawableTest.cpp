/**
 * \file CDrawableTest.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "CppUnitTest.h"
#include "Drawable.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;


namespace Testing
{
	class CDrawableMock : public CDrawable
	{
	public:
		CDrawableMock(const std::wstring& name) : CDrawable(name) {}

		virtual void Draw(Gdiplus::Graphics* graphics) override {}
		virtual bool HitTest(Gdiplus::Point pos) override { return false; }

	};

	TEST_CLASS(CDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCDrawableConstructorAndGetter)
		{
			CDrawableMock drawable(L"Winnie");
			Assert::AreEqual(std::wstring(L"Winnie"), drawable.GetName());
		}

		TEST_METHOD(TestCDrawablePosition)
		{
			CDrawableMock drawable(L"Winnie");

			// Default position
			Assert::AreEqual(0, drawable.GetPosition().X);
			Assert::AreEqual(0, drawable.GetPosition().Y);

			// Setter and Getter for position
			Gdiplus::Point position = Gdiplus::Point(1, 2);
			drawable.SetPosition(position);
			Assert::AreEqual(1, drawable.GetPosition().X);
			Assert::AreEqual(2, drawable.GetPosition().Y);
		}

		TEST_METHOD(TestCDrawableRotation)
		{
			CDrawableMock drawable(L"Winnie");

			// Default rotation value
			Assert::AreEqual(0, drawable.GetRotation(), 0);

			// Setter and Getter for rotation
			double a = 0.333;
			drawable.SetRotation(a);
			Assert::AreEqual(a, drawable.GetRotation(), 0.000000001);

		}

		TEST_METHOD(TestCDrawableAssociation)
		{
			CDrawableMock body(L"Body");
			auto arm = std::make_shared<CDrawableMock>(L"Arm");
			auto leg = std::make_shared<CDrawableMock>(L"Leg");

			Assert::IsNull(arm->GetParent());
			Assert::IsNull(leg->GetParent());

			body.AddChild(arm);
			body.AddChild(leg);

			Assert::IsTrue(arm->GetParent() == &body);
			Assert::IsTrue(leg->GetParent() == &body);
		}
	};
}