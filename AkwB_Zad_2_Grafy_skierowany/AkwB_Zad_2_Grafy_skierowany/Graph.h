#pragma once
#include "Verticle.h"


class Graph
{

	std::vector <Verticle> all_verticles;
	std::unordered_map <std::string, std::string> prev_neighbours_map;
	bool czy_liniowy = 1;

	std::vector<std::vector<std::string>> adjoint_vector;
	std::unordered_map <std::string, std::string> adjoint_map;

public:
	Graph();

	void Get_czy_liniowy();

	void add_verticle(Verticle wiercholek);

	Result is_graph_adjoint();
	
	void Show_prev_neighbour_map();

	void show_prev_neighbours_for_each_verticle();

	void preparing_graph();

	void create_adjoint_graph();

	std::unordered_map <std::string, std::string> Get_adjoint_map();
	
private :

	std::string generate_next_neighbour_list_for_graph();

	void generate_prev_neighbours_map_for_graph();

	void Create_unordered_set_for_each_verticle();

	std::string generate_prev_neighbour_list_for_graph();

	void create_adjoint_vector();

	int szukanie_w_wektorze_po_nazwie(std::string szukana_nazwa);

	int szukanie_w_wektorze_wejscia_i_wyjscia(std::string szukana_nazwa);

	void glue_edges_in_adjoint_verticle();
			
	void create_adjoint_next_neighbours_map();	

};


