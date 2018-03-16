#pragma once
#include "City.hpp"
#include <vector>
#include <algorithm>

struct Tour {
	static constexpr int CITIES_IN_TOUR = 20;
	double fitness;
	std::vector<City> permutation{ CITIES_IN_TOUR };

	Tour() {}
	~Tour() {}

	Tour(double input_fitness, std::vector<City>& input_permutation) {
		fitness = input_fitness;
		for (int i = 0; i < permutation.size(); i++) {
			permutation[i] = input_permutation[i];
		}
		random_shuffle(permutation.begin(), permutation.end()); //shuffle permutation
	}
};
