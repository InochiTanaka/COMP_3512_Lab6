#include "genetic_algorithm.hpp"

/* Gentic Algorithm works to generate high quality solution of problems like optimization and serch problems.
	In this program, serching the shortest distance of cities by rundam generating data. 
	For Gentic Algorithm, generating better data by three ways as mutation, crossover and selection. 
	After the ordered number of negerating iteration, find the shortest distance one as the result.
	
	By my C++ implimentation, improving some part compare with C implementation.
	For example, made easy to access array by implimeting vector. 
	Also, avoiding assigning data by making getter and setter on each structs.
	In additon, made simple structer by selapating City and Tour class on each files.
	*/

int main(void)
{
	Genetic_Algorithm test;
	return 0;
}

Genetic_Algorithm::Genetic_Algorithm()
{
	/* Variables */
	int    index_of_shortest_tour = 0;
	double best_distance = 0.0;
	double best_iteration_distance = 0.0;
	double improvement_factor = 0.3;

	/* Declares and Initializes the pointers to our dynamically allocated memory. */
	std::vector<Tour> population(POPULATION_SIZE);							// Holds our candidate population
	std::vector<Tour> parents;												// Used during crossover
	std::vector<Tour> crosses{ POPULATION_SIZE - NUMBER_OF_ELITES };        // Used during calculations
	std::vector<City> cities_to_visit(CITIES_IN_TOUR);
	Tour child;
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

	//Define best_distance
	best_distance = FITNESS_SCALER / (population[index_of_shortest_tour]).getFitness();
	printf("Shortest distance in initial population: %8.3f\n", best_distance);


	/* And now we loop until we find what we want--the population "evolves"!
	We can loop a certain number of times like:
	for (iterations = 0; iterations < ITERATIONS; ++iterations) { ... }

	OR

	We can loop until we observe a predetermined improvement:
	while ( best_distance / base_distance > improvement_factor) { ... } */
	for (int iterations = 0; iterations < ITERATIONS; iterations++) {

		/* 1. Selection: keep the best route by moving the fittest to the front of
		the population.  We won't  change it in this iteration, and we will
		call it an 'elite' individual) */
		if (index_of_shortest_tour != 0) {
			Tour temporary_tour = population[0];
			population[0] = population[index_of_shortest_tour];
			population[index_of_shortest_tour] = temporary_tour;
		}

		/* 2. Crossover (mix the rest of the routes and create new routes).  First
		we create a separate collection of POPULATION_SIZE - 1.  We store this
		in one of our utility buffers.  We choose parents by selecting the
		fittest tour from PARENT_POOL_SIZE randomly selected tours.  We do
		this NUMBER_OF_PARENTS times.  We cross the NUMBER_OF_PARENTS parents
		and store the result in our utility buffer
		*/
		for (int j = 0; j < (POPULATION_SIZE - NUMBER_OF_ELITES); ++j) {
			parents = select_parents(population);
			child = crossover(parents);
			crosses[j] = child;
		}

		/* Then we copy the POPULATION_SIZE - NUMBER_OF_ELITES crosses from the utility buffer
		to our population array, making sure not to overwrite the elite tour */
		for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
			population[i] = crosses[i - NUMBER_OF_ELITES];
			population[i].setFitness(0.0);
		}

		/* 3. Mutation (randomly mess a few up. excluding the elite tour[s]) */
		mutate(population);

		/* 4. Evaluation (assign each one a fitness aka FITNESS_SCALER * the inverse
		of the total distance traveled) */
		index_of_shortest_tour = determine_fitness(population, POPULATION_SIZE);

		/* At the end of this iteration, if we have made it further to our goal,
		we print some helpful information to standard output, and keep track */
		best_iteration_distance = population[index_of_shortest_tour].get_tour_distance();
		if (best_iteration_distance < best_distance) {
			best_distance = best_iteration_distance;
			printf("New distance: %8.3f\n", best_iteration_distance);
		}
	}

	/* Prints summary information */
	printf("Shortest distance %8.3f\n",
		(FITNESS_SCALER / population[index_of_shortest_tour].getFitness()));

	//Release memory of vectors
	std::vector<Tour>().swap(population);
	std::vector<Tour>().swap(parents);
	std::vector<Tour>().swap(crosses);
	std::vector<City>().swap(cities_to_visit);
}

int Genetic_Algorithm::determine_fitness(std::vector<Tour>& population, int population_size)
{
	int index_of_shortest_tour = 0;
	double shortest_tour_in_population = (double)RAND_MAX;
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
			get_distance_between_cities                         
			(city_list.permutation[i], city_list.permutation[(i + 1) % CITIES_IN_TOUR]);
	}
	return distance;
}

double Genetic_Algorithm::get_distance_between_cities(City a, City b)
{
	return sqrt(pow((double)(a.x_coordinate - b.x_coordinate), 2.0) +
		pow((double)(a.y_coordinate - b.y_coordinate), 2.0));
}

std::vector<Tour> Genetic_Algorithm::select_parents(std::vector<Tour> population)
{
	int i = 0, j = 0, k = 0, parent_index = 0;

	/* Chooses the best from PARENT_POOL randomly selected tours */
	std::vector<Tour> parents(NUMBER_OF_PARENTS);
	std::vector<Tour> parent_pool(PARENT_POOL_SIZE);

	for (i = 0; i < NUMBER_OF_PARENTS; ++i) {
		for (j = 0; j < PARENT_POOL_SIZE; ++j) {
			k = rand() % POPULATION_SIZE;
			parent_pool[j] = population[k];
		}
		parent_index = determine_fitness(parent_pool, PARENT_POOL_SIZE);
		parents[i] = parent_pool[parent_index];
	}
	std::vector<Tour>().swap(parent_pool);
	return parents;
}

Tour Genetic_Algorithm::crossover(std::vector<Tour>& parents)
{
	Tour child;

	/* Here's how we use rand again.  We invoke the rand() function, and since
	we want the result to be between 0 and (CITIES_IN_TOUR - 1), we use the
	modulus operator */
	int boundary_index = rand() % CITIES_IN_TOUR;

	/* Sets the index of the mixed result to 0.0 */
	child.setFitness(0.0);

	/* Copies the first 'boundary_index' cities in order from parent 1 to the mixed
	result */
	for (int i = 0; i < boundary_index; i++) {
		child.getPermutation()[i] = parents[0].getPermutation()[i];

	}

	/* Fills the rest of the cells with cities from parent 2 */
	while (boundary_index < CITIES_IN_TOUR) {
		for (int i = 0; i < CITIES_IN_TOUR; ++i) {
			/* If the mixed tour doesn't already contain the city at that index in parent two... */
			if (!child.contains_city(boundary_index, parents[1].getPermutation()[i])) {

				/* ...then we add it from the second parent to the child... */
				child.getPermutation()[boundary_index] = parents[1].getPermutation()[i];

				/* And increment the boundary_index */
				boundary_index++;
			}
		}
	}

	return child;
}


void Genetic_Algorithm::mutate(std::vector<Tour> population)
{
	int i = 0, j = 0, k = 0;
	double mutates = 0.0;
	for (i = 0 + NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
		for (j = 0; j < CITIES_IN_TOUR; ++j) {
			mutates = (double)rand() / (double)RAND_MAX;
			if (mutates <= MUTATION_RATE) {
				k = rand() % CITIES_IN_TOUR;
				population[i].swap_cities(j, k);
			}
		}
	}
}