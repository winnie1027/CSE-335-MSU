/**
 * \file CPictureObserverTest.cpp
 *
 * \author Winnie Yang
 */


#include "pch.h"
#include "CppUnitTest.h"
#include "PictureObserver.h"
#include "Picture.h"
#include <memory>


using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	class CPictureObserverMock : public CPictureObserver
	{
	public:
		CPictureObserverMock() : CPictureObserver() {}

		virtual void UpdateObserver() override { mUpdated = true; }
	};

	TEST_CLASS(CPictureObserverTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCPictureObserverConstruct)
		{
			CPictureObserverMock observer;
		}

		TEST_METHOD(TestCPictureObserverOneObserver)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer.mUpdated);
		}

		TEST_METHOD(TestPictureObserverGetPicture)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create a mock observer object
			CPictureObserverMock observer;

			// And set it for the observer:
			observer.SetPicture(picture);

			// Let observer get the picture
			Assert::IsTrue(picture == observer.GetPicture());

		}

		TEST_METHOD(TestPictureObserverTwoObservers)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create first mock observer object
			CPictureObserverMock observer1;

			// Create second mock observer object
			CPictureObserverMock observer2;

			// And set it for observer 1
			observer1.SetPicture(picture);

			// And set it for observer 2
			observer2.SetPicture(picture);

			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);
			Assert::IsTrue(observer2.mUpdated);
		}
		
		TEST_METHOD(TestPictureObserverRemainingObserver)
		{
			// Allocate a CPicture object
			shared_ptr<CPicture> picture = make_shared<CPicture>();

			// Create first mock observer object
			CPictureObserverMock observer1;

			// And set it for observer 1
			observer1.SetPicture(picture);

			{
				// Create second mock observer object
				CPictureObserverMock observer2;

				// And set it for observer 2
				observer2.SetPicture(picture);
			}

			picture->UpdateObservers();

			Assert::IsTrue(observer1.mUpdated);
		}
	};
}