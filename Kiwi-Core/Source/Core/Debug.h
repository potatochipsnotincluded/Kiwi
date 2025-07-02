#pragma once
#include "Common.h"


#ifndef DIST

#define KW_LOG(txt) std::cout << "Bellum::Log:: " << txt << std::endl;

#define KW_ASSERT(b) if (!(b))  { std::cout << "Bellum::Error:: " << __FILE__ << " on " << __LINE__ << std::endl; std::exit(-1); }

#else

#define KW_LOG(txt)

#define KW_ASSERT(b) if (!b)  { std::exit(-1); }

#endif