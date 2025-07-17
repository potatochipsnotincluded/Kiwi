#include "Maths.h"

namespace Kiwi {

	static std::random_device s_RandomDevice; // Seed source
	static std::mt19937 s_Generator(s_RandomDevice()); // 32-bit Mersenne Twister

	float Kiwi::RandomFloat(float min, float max)
	{
		std::uniform_real_distribution<float> dist(min, max);
		return dist(s_Generator);
	}

	int32_t RandomInt(int32_t min, int32_t max)
	{
		std::uniform_int_distribution<int32_t> dist(min, max);
		return dist(s_Generator);
	}

	uint32_t RandomUInt(uint32_t min, uint32_t max)
	{
		std::uniform_int_distribution<uint32_t> dist(min, max);
		return dist(s_Generator);
	}

}
