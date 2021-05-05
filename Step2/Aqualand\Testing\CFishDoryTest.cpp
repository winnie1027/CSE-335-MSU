#include "pch.h"
#include "CppUnitTest.h"

#include "FishDory.h"
#include "Aquarium.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
    TEST_CLASS(CFishDoryTest)
    {
    public:

        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

        TEST_METHOD(TestCFishDoryConstruct)
        {
            // Construct an item to test
            CAquarium aquarium;
            CFishDory FishDory(&aquarium);
        }

        TEST_METHOD(TestCFishDoryHitTest)
        {
            // Create a fish to test
            CAquarium aquarium;
            CFishDory fish(&aquarium);

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