#pragma once
#include "Verticle.h"


class Graph
{
	std::vector <Verticle> all_verticles;
	std::unordered_map <std::string, std::string> prev_neighbours_map;

public:

	std::string generate_next_neighbour_list_for_graph()
	{
		std::string list;
		for (auto element : all_verticles)
		{
			list += element.generate_next_neighbour_list_for_verticle();
		}

		return list;
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

	void add_verticle(Verticle wiercholek)
	{
		all_verticles.emplace_back(wiercholek);
	}

	bool is_graph_adjoint()
	{
		auto size = all_verticles.size();
		for (unsigned int i = 0; i < size; i++)
		{
			for (unsigned int j = i + 1; j < size; j++)
			{
				if (!all_verticles[i].is_verticle_adjoint(all_verticles[j]))
				{
					//jesli dla jakiejkolwiek pary wierzcholkow mamy czesc wspolna inna niz wszystkie elementy lub zbior pusty
					//to graf nie moze byc sprzezony 
					return false;
				}
			}
		}
	}

	//void generate_prev_neighbours_list_for_graph()
	//{
	//	std::unordered_set<std::string> prev_neighbours_list_A;

	//	for (auto element_ktorego_poprzednikow_szukam : all_verticles)
	//	{
	//		//szukaj nazwy elementu w unordered_set nastepnych sasiadow rezsty wierzcholkow nalezacych do grafu
	//		//wierzcholek ktory zawiera nazwe elementu na swojej liscie nastepnikow jest poprzednikiem tego elementu

	//		std::string szukany_element = element_ktorego_poprzednikow_szukam.Get_name();
	//		std::string lista_poprzednikow = szukany_element + "< ";

	//		for (auto wierzcholek_ktorego_sasiadow_analizuje : all_verticles)
	//		{

	//			if (wierzcholek_ktorego_sasiadow_analizuje.Get_next_neighbours().count(szukany_element))
	//			{
	//				lista_poprzednikow += wierzcholek_ktorego_sasiadow_analizuje.Get_name() + "|";

	//			}

	//		}
	//		lista_poprzednikow.pop_back(); //aby na koncu zadnej linii nie bylo "|"
	//		//lista_poprzednikow += "\n";
	//		prev_neighbours_list_A.emplace(lista_poprzednikow);

	//	}
	//	prev_neighbours_list = prev_neighbours_list_A;
	//}


	//void fill_prev_neighbours_to_each_verticle_class()
	//{
	//	std::string szukana_nazwa;
	//	std::string all_prev_neighbours_in_one_string;
	//	std::string one_prev_neighbour;

	//	for (auto verticle : all_verticles)
	//	{
	//		szukana_nazwa = verticle.Get_name();
	//		szukana_nazwa += "<";
	//		//auto ptr = prev_neighbours_list.find(szukana_nazwa);
	//		for (std::string element : prev_neighbours_list)
	//		{
	//			if (element.rfind(szukana_nazwa, 0) == 0)
	//			{
	//				//std::cout << "Nie wskazuje na koniec\n";
	//				all_prev_neighbours_in_one_string = element;
	//				std::stringstream stream(all_prev_neighbours_in_one_string);
	//			}
	//			else
	//			{
	//				//std::cout << "wskazuje na koniec";
	//			}
	//		}
	//		/*while (!stream.eof())
	//		{
	//			std::getline(stream, one_prev_neighbour, '|');
	//			verticle.Set_prev_neighbours(one_prev_neighbour);
	//		}*/
	//	}
	//}

	//std::unordered_set<std::string> Get_prev_neighbours_list()
	//{
	//	return prev_neighbours_list;
	//}

	//void Show_prev_neighbours_list()
	//{
	//	for (auto element : prev_neighbours_list)
	//	{
	//		std::cout << element << "\n";
	//	}
	//}

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
		

		for (auto element : all_verticles)
		{
			szukany_w_mapie = element.Get_name() + "<";
			wszyscy_poprzednicy = prev_neighbours_map[szukany_w_mapie];
			std::stringstream stream(wszyscy_poprzednicy); // ???????????????????czy ja na pewno moge robic to w petli

			while (!stream.eof())
			{
				std::getline(stream, jeden_poprzednik, '|');
				element.Set_prev_neighbour(jeden_poprzednik);
			}
			
		}
	}

	//bool is_graph_linear()  //jesli maja wspolne nastepniki to nie moga miec wspolnych poprzednikow. Jesli nie maja wspolnych poprzednikow to moga miec
	//{

	//	for (auto element_1 : all_verticles)
	//	{
	//		std::string szukana_nazwa = element_1.Get_name();
	//		szukana_nazwa + "<";

	//			
	//		for (auto element_2 : all_verticles)
	//		{


	//		}

	//	}

	//	return true;
	//}

};

