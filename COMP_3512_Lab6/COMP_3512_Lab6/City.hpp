#pragma once

struct City {
	static constexpr int CITIES_IN_TOUR = 20;

	char name;
	int  x_coordinate;
	int  y_coordinate;

	City() {}

	~City() {}

	City(char input_name, int input_x, int input_y) {
		name = input_name;
		x_coordinate = input_x;
		y_coordinate = input_y;
	}

	City(const City& input_city) {
		name = input_city.name;
		x_coordinate = input_city.x_coordinate;
		y_coordinate = input_city.y_coordinate;
	}

	char get_name() const { return name; }
	int get_x() const { return x_coordinate; }
	int get_y() const { return y_coordinate; }
};