#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

enum Result
{
	Nie_sprzezony = 0,
	Liniowy = 1,
	Do_sprawdzenia_czy_liniowy = 2,
	Czesc_wspolnych_nastepnikow = 3
};

class Verticle
{
	std::string name;
	std::unordered_set <std::string> verticle_next_neighbours;
	std::unordered_set <std::string> verticle_prev_neighbours;

public:

	void Set_name(std::string signature);

	std::string Get_name();

	std::unordered_set <std::string>  Get_next_neighbours();

	std::unordered_set <std::string>  Get_prev_neighbours();

	void Show_prev_neighbours();

	Verticle(std::string line_from_file);


	Result is_verticle_adjoint(Verticle wierzcholek);

	void Set_prev_neighbour(std::string str_prev_neigh);


	bool is_there_any_common_next_neighbour_between_two_verticles(Verticle wierzcholek_A);

	bool is_there_any_common_prev_neighbour_between_two_verticle(Verticle wierzcholek_A);
	
	bool is_there_any_common_neighbours(std::unordered_set<std::string> neighbours, std::unordered_set<std::string> neighboursToCompare);
};


