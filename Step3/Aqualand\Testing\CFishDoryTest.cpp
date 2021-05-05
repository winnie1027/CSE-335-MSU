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
    };
}