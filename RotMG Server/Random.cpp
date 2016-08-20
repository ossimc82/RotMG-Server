#include "Random.h"

#include <random>
#include <math.h>

unsigned int Random::nextInt() {
	return gen();
}

double Random::nextDouble() {
	return gen() / 2147483647;
}

int Random::nextNormal(double mean, double stdDev) {
	double u1 = gen() / 2147483647;
	double u2 = gen() / 2147483647;
	double r = sqrt(-2 * log(u1)) * cos((2 * u2) * 3.141592653589793);
	return mean + (r * stdDev);
}

int Random::nextIntRange(int min, int max) {
	return min == max ? min : min + (gen() % (max - min));
}

double Random::nextDoubleRange(double min, double max) {
	return min + ((max - min) * nextDouble());
}

unsigned int Random::randomSeed() {
	return lround(((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) *
		(UINT32_MAX - 1)) + 1);
}

unsigned int Random::gen() {
	unsigned int hi;
	unsigned int lo;

	lo = 16807 * (seed & 0xFFFF);
	hi = 16807 * (seed >> 16);
	lo = lo + ((hi & 32767) << 16);
	lo = lo + (hi >> 15);
	if (lo > 2147483647) {
		lo = (lo - 2147483647);
	}
	return seed = lo;
}
