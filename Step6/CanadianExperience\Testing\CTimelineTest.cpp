/**
 * \file CTimelineTest.cpp
 *
 * \author Winnie Yang
 */



#include "pch.h"
#include "CppUnitTest.h"
#include "Timeline.h"
#include "AnimChannelAngle.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CTimelineTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
        TEST_METHOD(TestCTimelineGetNumFrames)
        {
            CTimeline timeline;

            // Default number of frames
            Assert::AreEqual(300, timeline.GetNumFrames());

            // Changed number of frames
            timeline.SetNumFrames(500);
            Assert::AreEqual(500, timeline.GetNumFrames());
        }
        
        TEST_METHOD(TestCTimelineGetFrameRate)
        {
            CTimeline timeline;

            // Default frame rate
            Assert::AreEqual(30, timeline.GetFrameRate());

            // Changed frame rate
            timeline.SetFrameRate(50);
            Assert::AreEqual(50, timeline.GetFrameRate());
        }

        TEST_METHOD(TestCTimelineGetCurrentTime)
        {
            CTimeline timeline;

            // Default current time
            Assert::AreEqual(0.0, timeline.GetCurrentTime());

            timeline.SetCurrentTime(4.3);
            Assert::AreEqual(4.3, timeline.GetCurrentTime());
        }
        TEST_METHOD(TestCTimelineGetDuration)
        {
            CTimeline timeline;

            // Default value
            Assert::AreEqual(10, timeline.GetDuration(), 0.0001);

            // Changed duration
            timeline.SetFrameRate(375);
            Assert::AreEqual(300.0 / 375.0, timeline.GetDuration(), 0.0001);

            timeline.SetNumFrames(789);
            Assert::AreEqual(789.0 / 375.0, timeline.GetDuration(), 0.0001);
        }

        TEST_METHOD(TestCTimelineGetCurrentFrame)
        {
            CTimeline timeline;

            // Default value
            Assert::AreEqual(0, timeline.GetCurrentFrame());

            // Changed time
            timeline.SetCurrentTime(9.27);
            Assert::AreEqual(278, timeline.GetCurrentFrame());
        }

        TEST_METHOD(TestCTimelineAdd)
        {
            CTimeline timeline;
            CAnimChannelAngle channel;

            timeline.AddChannel(&channel);
            Assert::IsTrue(&timeline == channel.GetTimeline());
        }
	};
}