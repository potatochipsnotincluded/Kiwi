#pragma once
#include "Common.h"

namespace Kiwi {

	template <typename... Args>
	void FmtPrnt(std::format_string<Args...> fmt, Args&&... args)
	{
		std::println("Kiwi::Log:: {}", std::format(fmt, std::forward<Args>(args)...));
	}

	void AssertLg(auto msg, bool val)
	{
		if (!val)
		{
			std::println("Kiwi::Error:: {} on at {} on line {} ", msg, __FILE__, __LINE__);
			std::exit(1);
		}
	}

	void AssertDist(auto msg, bool val)
	{
		if (!val)
		{
			std::exit(1);
		}
	}

}

#ifndef DIST

#define KW_LOG(...) Kiwi::FmtPrnt(__VA_ARGS__)

#define KW_ASSERT(message, b) Kiwi::AssertLg(message, b)

#else

#define KW_LOG(txt)

#define KW_ASSERT(message, b) Kiwi::AssertDist(message, val)

#endif