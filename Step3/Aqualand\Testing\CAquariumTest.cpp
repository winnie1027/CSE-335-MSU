#include "pch.h"
#include "CppUnitTest.h"

#include "Aquarium.h"
#include "Fishbeta.h"
#include "DecorCastle.h"
#include "FishDory.h"
#include "Magikarp.h"

#include <regex>
#include <string>
#include <fstream>
#include <streambuf>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

const unsigned int RandomSeed = 1238197374;

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

		/**
		* Create a path to a place to put temporary files
		*/
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		* Read a file into a wstring and return it.
		* \param filename Name of the file to read
		* \return File contents
		*/
		wstring ReadFile(const wstring& filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}

		/**
		* Test to ensure an aquarium .aqua file is empty
		*/
		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua/>")));
		}

		/**
		*  Populate an aquarium with three Beta fish
		*/
		void PopulateThreeBetas(CAquarium* aquarium)
		{
			srand(RandomSeed);

			shared_ptr<CFishBeta> fish1 = make_shared<CFishBeta>(aquarium);
			fish1->SetLocation(100, 200);
			aquarium->Add(fish1);

			shared_ptr<CFishBeta> fish2 = make_shared<CFishBeta>(aquarium);
			fish2->SetLocation(400, 400);
			aquarium->Add(fish2);

			shared_ptr<CFishBeta> fish3 = make_shared<CFishBeta>(aquarium);
			fish3->SetLocation(600, 100);
			aquarium->Add(fish3);
		}

		void TestThreeBetas(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure three items
			Assert::IsTrue(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

			// Ensure the positions are correct
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

			// Ensure the types are correct
			Assert::IsTrue(regex_search(xml,
				wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));

		}

		void PopulateAllTypes(CAquarium* aquarium)
		{
			srand(RandomSeed);

			shared_ptr<CFishBeta> beta = make_shared<CFishBeta>(aquarium);
			beta->SetLocation(100, 200);
			aquarium->Add(beta);

			shared_ptr<CDecorCastle> castle = make_shared<CDecorCastle>(aquarium);
			castle->SetLocation(600, 100);
			aquarium->Add(castle);

			shared_ptr<CFishDory> dory = make_shared<CFishDory>(aquarium);
			dory->SetLocation(300, 300);
			aquarium->Add(dory);

			shared_ptr<CMagikarp> magikarp = make_shared<CMagikarp>(aquarium);
			magikarp->SetLocation(500, 200);
			aquarium->Add(magikarp);
		}

		TEST_METHOD(TestClear)
		{
			// Create an aquarium
			CAquarium aquarium;

			// Add fish to the aquarium
			PopulateAllTypes(&aquarium);

			// Clearing the aquarium
			aquarium.Clear();

			// There's no fish at all locations
			Assert::IsTrue(aquarium.HitTest(100, 200) == nullptr);
			Assert::IsTrue(aquarium.HitTest(400, 400) == nullptr);
			Assert::IsTrue(aquarium.HitTest(600, 100) == nullptr);
			Assert::IsTrue(aquarium.HitTest(300, 300) == nullptr);
			Assert::IsTrue(aquarium.HitTest(500, 200) == nullptr);
		}

		void TestAllTypes(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Test all items' location
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"300\" y=\"300\"")));
			Assert::IsTrue(regex_search(xml, wregex(L"<item x=\"500\" y=\"200\"")));

			// Test all items' type
			Assert::IsTrue(regex_search(xml, wregex(L"type=\"beta\"/")));
			Assert::IsTrue(regex_search(xml, wregex(L"type=\"castle\"/")));
			Assert::IsTrue(regex_search(xml, wregex(L"type=\"dory\"/")));
			Assert::IsTrue(regex_search(xml, wregex(L"type=\"magi\"/")));
		}

		void TestBetaSpeed(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			Assert::IsTrue(regex_search(xml,
				wregex(L"<item x=\"100\" y=\"200\" speedx=\"331\\.28604.*\" speedy=\"452\\.26294.*\"")));
			Assert::IsTrue(regex_search(xml,
				wregex(L"<item x=\"400\" y=\"400\" speedx=\"258\\.76033.*\" speedy=\"460\\.58534.*\"")));
			Assert::IsTrue(regex_search(xml,
				wregex(L"<item x=\"600\" y=\"100\" speedx=\"220\\.34821.*\" speedy=\"53\\.87279.*\"")));
		}

		void TestAllSpeed(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			Assert::IsTrue(regex_search(xml,
				wregex(L"<item x=\"100\" y=\"200\" speedx=\"331\\.28604.*\" speedy=\"452\\.26294.*\"")));
			Assert::IsTrue(regex_search(xml,
				wregex(L"<item x=\"300\" y=\"300\" speedx=\"485\\.56474.*\" speedy=\"664\\.96475.*\"")));
			Assert::IsTrue(regex_search(xml,
				wregex(L"<item x=\"500\" y=\"200\" speedx=\"144\\.63789.*\" speedy=\"52\\.15155.*\"")));
		}
		TEST_METHOD(TestCAquariumSave)
		{
			srand(RandomSeed);

			// Create a path to temporary files
			wstring path = TempPath();

			// Create an aquarium
			CAquarium aquarium;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";
			aquarium.Save(file1);

			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);

			TestThreeBetas(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);

			TestAllTypes(file3);
		}

		TEST_METHOD(TestCAquariumLoad)
		{
			srand(RandomSeed);

			// Create a path to temporary files
			wstring path = TempPath();

			// Create two aquariums
			CAquarium aquarium, aquarium2;

			//
			// First test, saving an empty aquarium
			//
			wstring file1 = path + L"test1.aqua";

			aquarium.Save(file1);
			TestEmpty(file1);

			aquarium2.Load(file1);
			aquarium2.Save(file1);
			TestEmpty(file1);

			//
			// Now populate the aquarium
			//

			PopulateThreeBetas(&aquarium);

			wstring file2 = path + L"test2.aqua";
			aquarium.Save(file2);
			TestThreeBetas(file2);
			TestBetaSpeed(file2);

			aquarium2.Load(file2);
			aquarium2.Save(file2);
			TestThreeBetas(file2);
			TestBetaSpeed(file2);

			//
			// Test all types
			//
			CAquarium aquarium3;
			PopulateAllTypes(&aquarium3);

			wstring file3 = path + L"test3.aqua";
			aquarium3.Save(file3);
			TestAllTypes(file3);
			TestAllSpeed(file3);

			aquarium2.Load(file3);
			aquarium2.Save(file3);
			TestAllTypes(file3);
			TestAllSpeed(file3);
		}
	};
}