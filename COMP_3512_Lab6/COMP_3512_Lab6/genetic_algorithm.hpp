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

#include <vector>
#include <iostream>
#include <utility>
#include <stack>

using namespace std;

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
	struct stack<city> permutation;
};


