#include "genetic_algorithm.hpp"


int Main()
{

	/* Declares the pointers to our dynamically allocated memory. */
	struct tour * population;      // Holds our candidate population
	struct tour * parents;         // Used during crossover
	struct tour * crosses;         // Used during calculations
	struct tour * temporary_tour;  // Used during calculations
	struct city * cities_to_visit; // Stores master list of cities
	struct tour * child;
}

void shuffle_cities(city * permutation)
{
}

double get_distance_between_cities(city a, city b)
{
	return 0.0;
}

double get_tour_distance(tour city_list)
{
	return 0.0;
}

int determine_fitness(tour * population, int population_size)
{
	return 0;
}

void swap_cities(int index_one, int index_two, city * permutation)
{
}

tour * select_parents(tour * population)
{
	return nullptr;
}

tour * crossover(tour * parents)
{
	return nullptr;
}

void mutate(tour * population)
{
}

int contains_city(tour * candidate_tour, int length, city * candidate_city)
{
	return 0;
}
