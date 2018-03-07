#pragma once

/* Definitions and then prototypes here */
#define POPULATION_SIZE 30
#define CITIES_IN_TOUR  20

/* A city structure contains:
a) a name
b) x and y coordinates */
struct city {
	char name;
	int  x_coordinate;
	int  y_coordinate;
};

/* A tour structure contains:
a) a fitness rating
b) an array of CITIES_IN_TOUR cities */
struct tour {
	double fitness;
	struct city permutation[CITIES_IN_TOUR];
};

void shuffle_cities(struct city * permutation);

double get_distance_between_cities(city city_a, city city_b);

double get_tour_distance(struct tour city_list);

int determine_fitness(struct tour * population, int population_size);

void swap_cities(city city_a, city city_b);

struct tour * select_parents(struct tour * population);

struct tour * crossover(struct tour * parents);

void mutate(struct tour * population);

int contains_city(struct tour * candidate_tour, int length, struct city * candidate_city);