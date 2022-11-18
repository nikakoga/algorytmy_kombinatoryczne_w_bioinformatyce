#pragma once
#include "Verticle.h"


class Graph
{
	std::vector <Verticle> all_verticles;
	std::unordered_map <std::string, std::string> prev_neighbours_map;
	bool czy_liniowy = 1;

public:

	void Get_czy_liniowy()
	{
		if (czy_liniowy)
		{
			std::cout << "Graf jest liniowy\n";
		}

		else
		{
			std::cout << "Graf nie jest liniowy\n";
		}	
		
	}

	std::string generate_next_neighbour_list_for_graph()
	{
		std::string list;
		for (auto element : all_verticles)
		{
			list += element.generate_next_neighbour_list_for_verticle();
		}

		return list;
	}

	void add_verticle(Verticle wiercholek)
	{
		all_verticles.emplace_back(wiercholek);
	}

	Result is_graph_adjoint()
	{
		auto size = all_verticles.size();
		for (unsigned int i = 0; i < size; i++)
		{
			for (unsigned int j = i + 1; j < size; j++)
			{
				if (all_verticles[i].is_verticle_adjoint(all_verticles[j])==Czesc_wspolnych_nastepnikow)
				{
					//jesli dla jakiejkolwiek pary wierzcholkow mamy czesc wspolna inna niz wszystkie elementy lub zbior pusty
					//to graf nie moze byc sprzezony 
					return Nie_sprzezony;
				}

				// to sa wierzcholki ktore maja wspolne nastepniki, wiec sprawdzam czy poprzedniki tez zeby wiedziec czy jest liniowy 
				else if (all_verticles[i].is_verticle_adjoint(all_verticles[j]) == Do_sprawdzenia_czy_liniowy)
				{
					if (all_verticles[i].is_there_any_common_prev_neighbour_between_two_verticle(all_verticles[j]))
					{
						czy_liniowy = 0;
					}
				}
				
			}
		}
	}


	void generate_prev_neighbours_map_for_graph()
	{

		for (auto element_ktorego_poprzednikow_szukam : all_verticles)
		{
			//szukaj nazwy elementu w unordered_set nastepnych sasiadow rezsty wierzcholkow nalezacych do grafu
			//wierzcholek ktory zawiera nazwe elementu na swojej liscie nastepnikow jest poprzednikiem tego elementu

			std::string szukany_element = element_ktorego_poprzednikow_szukam.Get_name();
			std::string poprzedniki;
			std::string wierzcholek = szukany_element + "<";

			for (auto wierzcholek_ktorego_sasiadow_analizuje : all_verticles)
			{

				if (wierzcholek_ktorego_sasiadow_analizuje.Get_next_neighbours().count(szukany_element))
				{
					poprzedniki += wierzcholek_ktorego_sasiadow_analizuje.Get_name() + "|";

				}

			}
			if (!poprzedniki.empty()) //bo jesli nie bedzie poprzednikow to z pustego stringa nie mozna usuwac
			{
				poprzedniki.pop_back(); //aby na koncu zadnej linii nie bylo "|"
			}
			
			prev_neighbours_map[wierzcholek] = poprzedniki;
		}
	}
	void Show_prev_neighbour_map()
	{
		for (auto element : prev_neighbours_map)
		{
			std::cout << element.first <<
				element.second << std::endl;
		}
		
	}

	void Create_unordered_set_for_each_verticle()
	{
		std::string szukany_w_mapie;
		std::string wszyscy_poprzednicy;
		std::string jeden_poprzednik;
		
		
		for (auto& element : all_verticles)  //musi byc referencja & jesli petla ma modyfikowac obiekt
		{
			szukany_w_mapie = element.Get_name() + "<";
			wszyscy_poprzednicy = prev_neighbours_map[szukany_w_mapie];
			std::stringstream stream(wszyscy_poprzednicy); 

			while (!stream.eof())
			{
				std::getline(stream, jeden_poprzednik, '|');
				element.Set_prev_neighbour(jeden_poprzednik);
			}
			
		}
	}

	std::string generate_prev_neighbour_list_for_graph()
	{
		std::string list;
		for (auto element : all_verticles)
		{
			list += element.generate_prev_neighbour_list_for_verticle();
		}

		return list;
	}

	void show_prev_neighbours_for_each_verticle()
	{
		for (auto element : all_verticles)
		{
			std::cout<<element.Get_name();
			std::cout<<"<";
			element.Show_prev_neighbours();
		}
	}


};

