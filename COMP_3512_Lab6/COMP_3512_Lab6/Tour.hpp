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

	int contains_city(int length, City candidate_city)
	{
		int i = 0;
		for (i = 0; i < length; ++i) {
			if (permutation[i].get_name() == (char)candidate_city.get_name() &&
				permutation[i].get_x() == (int)candidate_city.get_x() &&
				permutation[i].get_y() == (int)candidate_city.get_y()) {
				return 1;
			}
		}
		return 0;
	}

	void swap_cities(int index_one, int index_two)
	{
		City temp = permutation[index_one];
		permutation[index_one] = permutation[index_two];
		permutation[index_two] = temp;
		return;
	}

	double get_tour_distance()
	{
		int i = 0;
		double distance = 0.0;
		for (i = 0; i < CITIES_IN_TOUR; ++i) {
			distance += get_distance_between_cities(permutation[i], permutation[(i + 1) % CITIES_IN_TOUR]);
		}
		return distance;
	}

	double get_distance_between_cities(City a, City b)
	{
		return sqrt(pow((double)(a.x_coordinate - b.x_coordinate), 2.0) +
			pow((double)(a.y_coordinate - b.y_coordinate), 2.0));
	}

	double getFitness() const {
		return fitness;
	}

	void setFitness(double input_fitness) {
		fitness = input_fitness;
	}

	std::vector<City>& getPermutation() {
		return permutation;
	}
};
