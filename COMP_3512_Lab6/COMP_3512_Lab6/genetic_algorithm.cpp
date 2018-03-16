#include "genetic_algorithm.hpp"

int main(void)
{
	Genetic_Algorithm test;
	return 0;
}

Genetic_Algorithm::Genetic_Algorithm()
{
	/* Variables */
	int    index_of_shortest_tour = 0;
	//double best_distance = 0.0;
	//double best_iteration_distance = 0.0;
	//double improvement_factor = 0.3;

	/* Declares and Initializes the pointers to our dynamically allocated memory. */
	std::vector<Tour> population(POPULATION_SIZE);      // Holds our candidate population
	std::vector<Tour> parents;         // Used during crossover
	std::vector<Tour> crosses{ POPULATION_SIZE - NUMBER_OF_ELITES };         // Used during calculations
	std::vector<Tour> temporary_tour;  // Used during calculations
	std::vector<City> cities_to_visit(CITIES_IN_TOUR);
	std::vector<Tour> child;
	srand((unsigned int)time(NULL));

	// Declares and defines the master list of all the cities that we need to visit.
	// The cities are named 'A', 'B', ... , and they each have a random X and Y	coordinate */
	for (int i = 0; i < CITIES_IN_TOUR; ++i) {
		cities_to_visit[i] = City((char)(i + ASCII_OFFSET), rand() % (MAP_BOUNDARY + 1), rand() % (MAP_BOUNDARY + 1));
	}

	//Storing cities_to_visit component to population vector array
	for (int i = 0; i < POPULATION_SIZE; i++) {
		population[i] = Tour(0, cities_to_visit);
	}

	//find "index_of_shortest_tour"
	index_of_shortest_tour = determine_fitness(population, POPULATION_SIZE);


}

int Genetic_Algorithm::determine_fitness(std::vector<Tour>& population, int population_size)
{
	int index_of_shortest_tour = 0;
	double shortest_tour_in_population = (double)RAND_MAX; // Begin by assuming distance is enormous
	double candidate_distance = 0.0;

	for (int i = 0; i < population_size; ++i) {
		candidate_distance = get_tour_distance(population[i]);
		population[i].fitness = FITNESS_SCALER / candidate_distance;
		if (candidate_distance <= shortest_tour_in_population) {
			index_of_shortest_tour = i;
			shortest_tour_in_population = candidate_distance;
		}
	}

	return index_of_shortest_tour;
}

double Genetic_Algorithm::get_tour_distance(Tour city_list)
{
	int i = 0;
	double distance = 0.0;
	for (i = 0; i < CITIES_IN_TOUR; ++i) {
		distance +=
			get_distance_between_cities                         // so we create a loop
			(city_list.permutation[i], city_list.permutation[(i + 1) % CITIES_IN_TOUR]);
	}
	return distance;
}

double Genetic_Algorithm::get_distance_between_cities(City a, City b)
{
	return sqrt(pow((double)(a.x_coordinate - b.x_coordinate), 2.0) +
		pow((double)(a.y_coordinate - b.y_coordinate), 2.0));
}
