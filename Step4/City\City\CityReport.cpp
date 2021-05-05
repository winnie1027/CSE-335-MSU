/**
 * \file CityReport.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "CityReport.h"

using namespace std;

/**
 * Constructor
 * @param city City this report is for. 
*/
CCityReport::CCityReport(CCity* city) : mCity(city)
{
}

/**
 * Add a new city report
 * @param report Report to add
*/
void CCityReport::Add(std::shared_ptr<CMemberReport> report)
{
    if (mBins.empty() || (rand() % 100) > 50)
    {
        // Create a new, empty, bin at the end of the list
        mBins.push_back(Bin());
    }

    // Add to the last ben
    mBins.back().mReports.push_back(report);
}
