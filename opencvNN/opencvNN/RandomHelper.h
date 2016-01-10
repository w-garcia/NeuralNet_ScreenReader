#pragma once

#include <random>
#include <time.h>
#include <math.h>
#include <ctime>

static double randD(double min, double max)
{
	std::uniform_real_distribution<double> dist(min, max);
	std::mt19937 rng;
	rng.seed(std::random_device{}());
	return dist(rng);
}

static double randD()
{
	std::uniform_real_distribution<double> dist(-1.0, 1.0);
	std::mt19937 rng;
	rng.seed(std::random_device{}());
	return dist(rng);
}

static bool chance(double p)
{
	return p < randD();
}

static double sigmoidPrime(double x)
{
	return x * (1.0 - x);
}

static double hyperbolicTangent(double x)
{
	return 1.7159 * tanh((2 / 3)*x);
}

static double sigmoid(double x)
{
	return 1 / (1.0 + exp(-x));
}