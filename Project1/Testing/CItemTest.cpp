#include "pch.h"
#include "CppUnitTest.h"

#include "Game.h"
#include "Item.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;
using namespace std;


namespace Testing
{
	/** Mock class for testing CItem */
	class CItemMock : public CItem
	{
	public:
		CItemMock(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CItem(game, imagePair) {}

		virtual void Accept(CItemVisitor* visitor) override {}

		virtual void Halt() {}
	};

	TEST_CLASS(CItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCItemConstruct)
		{
			CGame game1;
			wstring filename1 = L"images/";
			wstring filename2 = L"images/";
			filename1 = filename1 + L"fox.png";
			filename2 = filename2 + L"fox-carried.png";
			shared_ptr<Bitmap> image1 = shared_ptr<Bitmap>(Bitmap::FromFile(filename1.c_str()));
			shared_ptr<Bitmap> image2 = shared_ptr<Bitmap>(Bitmap::FromFile(filename2.c_str()));
			std::pair< shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = make_pair(image1, image2);
			CItemMock item1(&game1, imagePair);
		}

		TEST_METHOD(TestCItemGettersSetters)
		{
			// Construct an item to test
			CGame game1;
			wstring filename1 = L"images/";
			wstring filename2 = L"images/";
			filename1 = filename1 + L"fox.png";
			filename2 = filename2 + L"fox-carried.png";
			shared_ptr<Bitmap> image1 = shared_ptr<Bitmap>(Bitmap::FromFile(filename1.c_str()));
			shared_ptr<Bitmap> image2 = shared_ptr<Bitmap>(Bitmap::FromFile(filename2.c_str()));
			std::pair< shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = make_pair(image1, image2);
			CItemMock item1(&game1, imagePair);

			// Test SetLocation, GetX, and GetY
			item1.SetLocation(10.5, 17.2);
			Assert::AreEqual(10.5, item1.GetX(), 0.0001);
			Assert::AreEqual(17.2, item1.GetY(), 0.0001);

			// Test a second with with different values
			item1.SetLocation(-72, -107);
			Assert::AreEqual(-72, item1.GetX(), 0.0001);
			Assert::AreEqual(-107, item1.GetY(), 0.0001);
		}
	};
}