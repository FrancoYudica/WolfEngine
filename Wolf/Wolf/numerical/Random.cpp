#include "Random.h"

using namespace Wolf::Numerical::Random;

RandomFloat::RandomFloat(uint32_t seed)
{
    _seed = seed;
    _distribution = std::uniform_real_distribution<float>(0.0f, 1.0f);
    _generator = std::mt19937(seed);
}

float RandomFloat::unit()
{
    return _distribution(_generator);
}

float RandomFloat::signed_unit()
{
    return _distribution(_generator) * 2.0f - 1.0f;
}

float RandomFloat::range(float min, float max)
{
    return min + _distribution(_generator) * (max - min);
}

RandomDouble::RandomDouble(uint32_t seed)
{
    _seed = seed;
    _distribution = std::uniform_real_distribution<double>(0.0f, 1.0f);
    _generator = std::mt19937(seed);
}

double RandomDouble::unit()
{
    return _distribution(_generator);
}

double RandomDouble::signed_unit()
{
    return _distribution(_generator) * 2.0f - 1.0f;
}

double RandomDouble::range(double min, double max)
{
    return min + _distribution(_generator) * (max - min);
}

static int32_t max_int = std::numeric_limits<int32_t>::max();

RandomInt::RandomInt(uint32_t seed)
{
    _seed = seed;
    _distribution = std::uniform_int_distribution<int32_t>(0, max_int);
    _generator = std::mt19937(seed);
}

int32_t RandomInt::unit()
{
    return _distribution(_generator);
}

int32_t RandomInt::signed_unit()
{
    return _distribution(_generator) * 2 - max_int;
}

int32_t RandomInt::range(int32_t min, int32_t max)
{
    return min + _distribution(_generator) * (max - min);
}
