/**
 * \file CPolygonDrawableTest.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "CppUnitTest.h"
#include "PolyDrawable.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CPolygonDrawableTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCPolyDrawableConstructorAndGetter)
		{
			CPolyDrawable drawable(L"Winnie");
			Assert::AreEqual(drawable.GetName(), std::wstring(L"Winnie"));
		}

		TEST_METHOD(TestCPolyDrawableColor)
		{
			CPolyDrawable drawable(L"Winnie");
			Gdiplus::Color color1 = Gdiplus::Color::Black;

			// default color
			Assert::AreEqual(drawable.GetColor().GetValue(), color1.GetValue());

			// Setter and Getter for color
			Gdiplus::Color color2 = Gdiplus::Color::Blue;
			drawable.SetColor(color2);
			Assert::AreEqual(drawable.GetColor().GetValue(), color2.GetValue());
		}
	};
}