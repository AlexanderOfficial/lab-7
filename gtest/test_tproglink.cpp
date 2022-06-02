#include "pch.h"
//#include "../Text/TTextProg.h"
#include "../Text/TTextProg.cpp"
//#include "../Text/TTextProg.cpp"
//#include "../Text/TProgLink.h"
#include "../Text/TProgLink.cpp"

TTextMem TProgLink::MemHeader;
TEST(TProgLink, can_init_mem_system)
{
	ASSERT_NO_THROW(TProgLink::InitMemSystem(100));
}

TEST(TProgLink, cant_init_mem_system_with_negative)
{
	ASSERT_ANY_THROW(TProgLink::InitMemSystem(-5));
}

