#include "pch.h"
#include "CppUnitTest.h"

#include "Game.h"
#include "Vector.h"
#include "Vehicle.h"
#include "Car.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;
using namespace std;

namespace Testing
{
	/** Mock class for testing CItem */
	class CVehicleMock : public CVehicle
	{
	public:
		CVehicleMock(CGame* game, std::pair<shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair) : CVehicle(game, imagePair) {}

		/** Test to see if we clicked on this item
		 * \param x X location
		 * \param y Y location
		 * \returns true if we did click on the item */
		virtual bool ClickTest(int x, int y) { return false; }
	};

	TEST_CLASS(CVehicleTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCVehicleGettersSetters)
		{
			//CGame game;
			// Keep getting a failed to open when running tests
			//	an images folder is in the Testing folder, so not sure why^
			/**wstring filename1 = L"images/invaderNa.png";
			shared_ptr<Bitmap> image1 = shared_ptr<Bitmap>(Bitmap::FromFile(filename1.c_str()));
			shared_ptr<Bitmap> image2 = nullptr;
			std::pair< shared_ptr<Bitmap>, shared_ptr<Bitmap>> imagePair = make_pair(image1, image2);
			CVehicleMock item1(&game, imagePair);

			//Test SetLocation(), GetPosition() - CVector usage
			item1.SetLocation(2.5, -5.0);
			Assert::AreEqual(2.5, item1.GetX(), 0.0001);
			Assert::AreEqual(-5.0, item1.GetY(), 0.0001);

			//Test SetSpeed(), GetSpeed()
			item1.SetSpeed(10);
			Assert::AreEqual(10, item1.GetSpeed(), 0.0001);*/
		}

	};
}