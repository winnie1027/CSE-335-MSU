#include "pch.h"
#include "CppUnitTest.h"
#include "City.h"
#include "CityReport.h"
#include "MemberReport.h"

#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileCoalmine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Testing
{
	TEST_CLASS(CCityReportTest)
	{
	public:
        /** Testing stub class, creates a vector from
         * the list. This is done so we can test this
         * before we create the iterator. DO NOT USE
         * THIS CODE to solve the iterator task */
        class CCityReportStub : public CCityReport
        {
        public:
            CCityReportStub(CCity* city) : CCityReport(city) {}

            std::vector<std::shared_ptr<CMemberReport>> GetReports()
            {
                std::vector<std::shared_ptr<CMemberReport>> list;

                // Iterate over the bins (list)
                for (std::list<CCityReport::Bin>::iterator iter = mBins.begin(); iter != mBins.end(); iter++)
                {
                    // Iterate over the contents of a bin (vector)
                    for (size_t i=0; i<iter->mReports.size(); i++)
                    {
                        list.push_back(iter->mReports[i]);
                    }

                }

                return list;
            }
        };

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}

        void AddTile(CCity* city, CCityReport* report, std::shared_ptr<CTile> tile)
        {
            city->Add(tile);

            auto memberReport = make_shared<CMemberReport>(tile);
            tile->Report(memberReport);
            report->Add(memberReport);
        }

        void AddLandscape(CCity* city, CCityReport* report, int x, int y)
        {
            auto tile = make_shared<CTileLandscape>(city);
            tile->SetLocation(x, y);
            AddTile(city, report, tile);
        }

        void AddBuilding(CCity* city, CCityReport* report, int x, int y, std::wstring file)
        {
            auto tile = make_shared<CTileBuilding>(city);
            tile->SetImage(file);
            tile->SetLocation(x, y);
            AddTile(city, report, tile);
        }


        void AddCoalmine(CCity* city, CCityReport* report, int x, int y)
        {
            auto tile = make_shared<CTileCoalmine>(city);
            tile->SetLocation(x, y);
            AddTile(city, report, tile);
        }
		
		TEST_METHOD(TestCCityReportAdd)
		{
            CCity city;     // We need a city

            // The report class under test
            CCityReportStub report(&city);

            auto results = report.GetReports();
            Assert::AreEqual(0, (int)results.size());

            AddLandscape(&city, &report, 100, 210);

            results = report.GetReports();
            Assert::AreEqual(1, (int)results.size());
            Assert::AreEqual(wstring(L"100, 210: Landscape"), results[0]->Report());

            AddBuilding(&city, &report, 30, 109, L"market.png");

            results = report.GetReports();
            Assert::AreEqual(2, (int)results.size());
            Assert::AreEqual(wstring(L"100, 210: Landscape"), results[0]->Report());
            Assert::AreEqual(wstring(L"30, 109: Building - market.png"), results[1]->Report());

            auto str = results[1]->Report();

            for (int i = 0; i < 100; i++)
            {
                AddLandscape(&city, &report, 100+i, 210);
                AddBuilding(&city, &report, 130, 200+i, L"market.png");
                AddCoalmine(&city, &report, 300+i, 299);
            }

            results = report.GetReports();
            Assert::AreEqual(302, (int)results.size());

            for (int i = 0; i < 100; i++)
            {
                wstringstream str1, str2, str3;
                str1 << 100 + i << ", 210: Landscape";
                str2 << "130, " << 200 + i << ": Building - market.png";
                str3 << 300 + i << ", 299: Coalmine - currently idle";

                Assert::AreEqual(str1.str(), results[i * 3 + 2]->Report());
                Assert::AreEqual(str2.str(), results[i * 3 + 3]->Report());
                Assert::AreEqual(str2.str(), results[i * 3 + 3]->Report());
            }

		}

        TEST_METHOD(TestCCitemReportIterator)
        {
            // We need a city
            CCity city;

            // The report class under test
            CCityReportStub report(&city);

            // Test to ensure the collection is initially empty
            auto results = report.GetReports();
            Assert::IsFalse(report.begin() != report.end());

            // Add one landscape tile
            AddLandscape(&city, &report, 100, 210);

            // Test that the iterator works with one item in the collection
            results = report.GetReports();
            // Get an iterator
            auto iter = report.begin();
            // Ensure the iterator points to the same thing as the know first
            // item in the collection.
            Assert::IsTrue(results[0]->Report() == (*iter)->Report());
            // Ensure the iterator things it is not at the end yet
            Assert::IsTrue(iter != report.end());
            // Increment, should increment to the end
            ++iter;
            Assert::IsFalse(iter != report.end());

            // Add one building tile
            AddBuilding(&city, &report, 30, 109, L"market.png");

            // Test that the iterator works with two items in the collection
            results = report.GetReports();
            iter = report.begin();
            Assert::IsTrue(results[0]->Report() == (*iter)->Report());
            Assert::IsTrue(iter != report.end());
            ++iter;
            Assert::AreEqual(results[1]->Report(), (*iter)->Report());
            Assert::IsTrue(iter != report.end());
            ++iter;
            Assert::IsFalse(iter != report.end());

            // Test with varying numbers of items in the collection
            for (int i = 0; i < 100; i++)
            {
                // Add three tiles
                AddLandscape(&city, &report, 100 + i, 210);
                AddBuilding(&city, &report, 130, 200 + i, L"market.png");
                AddCoalmine(&city, &report, 300 + i, 299);

                // Test the iterator
                results = report.GetReports();
                size_t cnt = 0;
                for (auto memberReport : report)
                {
                    Assert::IsTrue(cnt < results.size());
                    Assert::AreEqual(results[cnt]->Report(), memberReport->Report());

                    cnt++;
                }

            }

        }
	};
}