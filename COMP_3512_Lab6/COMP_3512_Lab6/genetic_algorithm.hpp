#pragma once

/* A city structure contains:
a) a name
b) x and y coordinates */
struct city {

};

/* A tour structure contains:
a) a fitness rating
b) an array of CITIES_IN_TOUR cities */
struct tour {

};

void shuffle_cities(struct city * permutation);

double get_distance_between_cities(struct city a, struct city b);

double get_tour_distance(struct tour city_list);

int determine_fitness(struct tour * population, int population_size);

void swap_cities(int index_one, int index_two, struct city * permutation);

struct tour * select_parents(struct tour * population);

struct tour * crossover(struct tour * parents);

void mutate(struct tour * population);

int contains_city(struct tour * candidate_tour, int length, struct city * candidate_city);