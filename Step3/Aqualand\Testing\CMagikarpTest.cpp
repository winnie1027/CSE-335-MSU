#include "pch.h"
#include "CppUnitTest.h"

#include "Magikarp.h"
#include "Aquarium.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
    TEST_CLASS(CMagikarpTest)
    {
    public:

        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

        TEST_METHOD(TestCMagikarpConstruct)
        {
            // Construct an item to test
            CAquarium aquarium;
            CMagikarp Magikarp(&aquarium);
        }
    };
}