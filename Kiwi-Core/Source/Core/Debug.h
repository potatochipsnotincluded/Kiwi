#pragma once
#include "Common.h"


#ifndef DIST

#define KW_LOG(txt) std::cout << "Kiwi::Log:: " << txt << std::endl;

#define KW_ASSERT(message, b) if (!(b))  { std::cout << "Kiwi::Error:: " << message << "in" << __FILE__ << " on " << __LINE__ << std::endl; std::exit(-1); }

#else

#define KW_LOG(txt)

#define KW_ASSERT(message, b) if (!b)  { std::exit(-1); }

#endif