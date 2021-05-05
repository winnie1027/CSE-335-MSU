#include "pch.h"
#include "CppUnitTest.h"
#include "Game.h"
#include "Item.h"
#include "Cargo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{
	TEST_CLASS(CGameTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCGameConstruct)
		{
			CGame game;
		}
		
		TEST_METHOD(TestCAquariumHitTest)
		{
			CGame game;

			Assert::IsTrue(game.ClickTest(100, 200) == nullptr,
				L"Testing empty game");


			//Need to figure out how to load cargo item here so I can perform hit test on it

			/*
			shared_ptr<CCargo> fox = make_shared<CCargo>(&game);
			fox->SetLocation(100, 200);

			Assert::IsTrue(game.ClickTest(500, 500) == nullptr,
				L"Testing fox at 500, 500");
			*/
			

			
		}

	};
}