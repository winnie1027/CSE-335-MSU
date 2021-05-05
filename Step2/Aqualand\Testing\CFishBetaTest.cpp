#include "pch.h"
#include "CppUnitTest.h"

#include "FishBeta.h"
#include "Aquarium.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
    TEST_CLASS(CFishBetaTest)
    {
    public:

        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

        TEST_METHOD(TestCFishBetaConstruct)
        {
            // Construct an item to test
            CAquarium aquarium;
            CFishBeta FishBeta(&aquarium);
        }

        TEST_METHOD(TestCFishBetaHitTest)
        {
            // Create a fish to test
            CAquarium aquarium;
            CFishBeta fish(&aquarium);

            // Give it a location
            // Always make the numbers different, in case they are mixed up
            fish.SetLocation(100, 200);

            // Center of the fish should be a true
            Assert::IsTrue(fish.HitTest(100, 200));

            // Left of the fish
            Assert::IsFalse(fish.HitTest(10, 200));

            // Right of the fish
            Assert::IsFalse(fish.HitTest(200, 200));

            // Above the fish
            Assert::IsFalse(fish.HitTest(100, 0));

            // Below the fish
            Assert::IsFalse(fish.HitTest(100, 300));

            // Of fish transparent pixel
            Assert::IsFalse(fish.HitTest(100 - 125 / 2 + 17, 200 - 117 / 2 + 16));
        }
    };
}