#pragma once
#include "Tour.hpp"
#include <cstdlib>
#include <ctime>

class Genetic_Algorithm {

	private:
		/* Definitions and then prototypes here */
		static constexpr int CITIES_IN_TOUR = 20;
		static constexpr int POPULATION_SIZE = 30;
		static constexpr int NUMBER_OF_PARENTS = 2;
		static constexpr int SHUFFLES = 32;
		static constexpr int ASCII_OFFSET = 65;
		static constexpr int ITERATIONS = 1000;
		static constexpr int MAP_BOUNDARY = 1000;
		static constexpr double FITNESS_SCALER = 10000.0;
		static constexpr int PARENT_POOL_SIZE = 5;
		static constexpr double MUTATION_RATE = 0.15;
		static constexpr int NUMBER_OF_ELITES = 1;

	public:
		Genetic_Algorithm();
		int determine_fitness(std::vector<Tour>& population, int poplulation_size);
		double get_tour_distance(Tour city_list);
		double get_distance_between_cities(City a, City b);
		std::vector<Tour> select_parents(std::vector<Tour> population);
		Tour crossover(std::vector<Tour>& parents);
		void mutate(std::vector<Tour> population);
};