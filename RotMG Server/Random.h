#ifndef RANDOM_H_
#define RANDOM_H_

class Random {
public:
	Random(unsigned int seed) { }
	Random() : Random(randomSeed()) { }
	unsigned int seed;

	unsigned int nextInt();
	double nextDouble();
	int nextNormal(double mean=0, double stdDev=1);
	int nextIntRange(int min, int max);
	double nextDoubleRange(double min, double max);
	
	static unsigned int randomSeed();
private:
	unsigned int gen();
};

#endif // !RANDOM_H_
