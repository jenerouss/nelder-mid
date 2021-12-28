#include <random>
#include <vector>


// set a seed for a starting point for generators
size_t seed = time(0);

// shift all generators
std::mt19937 generator_uni_i(seed);
std::mt19937 generator_uni_r(seed + 100);
std::mt19937 generator_norm(seed + 200);
std::mt19937 generator_cachy(seed + 300);
std::mt19937 generator_uni_i_2(seed + 400);

// different generators
std::uniform_int_distribution<int> uni_int(0, 32768);
std::uniform_real_distribution<double> uni_real(0.0, 1.0);
std::normal_distribution<double> norm_dist(0.0, 1.0);
std::cauchy_distribution<double> cachy_dist(0.0, 1.0);

// high-level functions
int rand_int(int max_int)
{
	if (max_int == 0)
		return 0;
	else
		return uni_int(generator_uni_i) % max_int;
}
double rand_uniform(double minimal, double maximal)
{
	return uni_real(generator_uni_r) * (maximal - minimal) + minimal;
}
double rand_normal(double mu, double sigma)
{
	return norm_dist(generator_norm) * sigma + mu;
}
double rand_cachy(double mu, double sigma)
{
	return cachy_dist(generator_cachy) * sigma + mu;
}