#include "pch.h"
#include "CppUnitTest.h"

#include "Aquarium.h"
#include "Fishbeta.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace Testing
{
	TEST_CLASS(CAquariumTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

		TEST_METHOD(TestCAquariumConstruct)
		{
			CAquarium aquarium;
		}

		TEST_METHOD(TestCAquariumHitTest)
		{
			CAquarium aquarium;

			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish at 100, 200");
		}

		TEST_METHOD(TestItemOverlap)
		{
			CAquarium aquarium;

			// Starting with an empty aquarium
			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			// Adding 2 fish which overlap each other
			std::shared_ptr<CFishBeta> fish = std::make_shared<CFishBeta>(&aquarium);
			fish->SetLocation(100, 200);
			aquarium.Add(fish);

			std::shared_ptr<CFishBeta> fish1 = std::make_shared<CFishBeta>(&aquarium);
			fish1->SetLocation(100, 200);
			aquarium.Add(fish1);

			// Since fish1 was added after fish, fish1 now takes the location (100, 200)
			Assert::IsFalse(aquarium.HitTest(100, 200) == fish,
				L"Testing fish at 100, 200 which should be replaced with fish1");

			Assert::IsTrue(aquarium.HitTest(100, 200) == fish1,
				L"Testing fish1 at 100, 200 which is replacing fish");
		}

		TEST_METHOD(TestNoItem)
		{
			CAquarium aquarium;

			// Make sure that the aquarium is empty first
			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr,
				L"Testing empty aquarium");

			// Adding a fish to location (100, 200)
			std::shared_ptr<CFishBeta> fish = std::make_shared<CFishBeta>(&aquarium);
			fish->SetLocation(100, 200);
			aquarium.Add(fish);

			// There's no fish at location (200, 200)
			Assert::IsTrue(aquarium.HitTest(200, 200) == nullptr,
				L"Testing fish that does not exist at 200, 200");
		}
	};
}