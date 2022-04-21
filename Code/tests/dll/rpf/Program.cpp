#include "pch.h"

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	// NOTE: You must change this to your own GTA 5 path! or tests will fail!
	//RPF::Init(L"D:\\Games\\Grand Theft Auto V\\GTA5.exe");

	return RUN_ALL_TESTS();
}
