#include <random>

using namespace std;

int generate_int(int minval, int maxval)
{
	random_device dev;
	mt19937 gen(dev());
	uniform_int_distribution<> dist(minval, maxval);

	return dist(gen);
}