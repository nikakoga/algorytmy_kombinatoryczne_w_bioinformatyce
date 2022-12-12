#include "Graph.h"

Graph::Graph() {}

void Graph::Get_czy_liniowy()
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

void Graph::add_verticle(Verticle wiercholek)
{
	all_verticles.emplace_back(wiercholek);
}

Result Graph::is_graph_adjoint_and_linear()
{
	auto size = all_verticles.size();
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = i + 1; j < size; j++)
		{
			if (all_verticles[i].is_verticle_adjoint(all_verticles[j]) == Czesc_wspolnych_nastepnikow)
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

void Graph::Show_prev_neighbour_map()
{
	for (auto element : prev_neighbours_map)
	{
		std::cout << element.first <<
			element.second << std::endl;
	}

}

void Graph::show_prev_neighbours_for_each_verticle()
{
	for (auto element : all_verticles)
	{
		std::cout << element.Get_name();
		std::cout << "<";
		element.Show_prev_neighbours();
	}
}



void Graph::generate_prev_neighbours_map_for_graph()
{

	for (auto element_ktorego_poprzednikow_szukam : all_verticles)
	{
		//szukam nazwy elementu w unordered_set nastepnych sasiadow reszty wierzcholkow nalezacych do grafu
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

void Graph::Create_unordered_set_for_each_verticle()
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


void Graph::create_helper_vector()
{

	int licznik = 1;
	int element = 0;

	for (auto wierzcholek : all_verticles)
	{
		adjoint_vector.emplace_back(std::vector<std::string>());

		adjoint_vector[element].emplace_back(wierzcholek.Get_name());

		adjoint_vector[element].emplace_back(std::to_string(licznik)); //to co wchodzi do wierzcholka
		licznik++;

		adjoint_vector[element].emplace_back(std::to_string(licznik)); //to co wychodzi z wierzcholka
		licznik++;

		element++;

	}
}

void Graph::show_adjoint_vector()
{
	for (auto element : adjoint_vector)
	{
		std::cout << element[0] << " " << element[1] << " " << element[2] << "\n";
	}

	std::cout << "\n\n";
}

int Graph::szukanie_w_wektorze_po_nazwie(std::string szukana_nazwa)
{
	for (int i = 0; i < adjoint_vector.size(); i++)
	{
		if (adjoint_vector[i][0] == szukana_nazwa)
		{
			return i;
		}
	}

	throw std::invalid_argument("ERROR blad w wektorze do tworzenia grafu oryginalnego - nie moge znalezc wierzcholka o tym imieniu\n");

}

int Graph::szukanie_w_wektorze_wejscia_i_wyjscia(std::string szukana_nazwa)
{

	for (int i = 0; i < adjoint_vector.size(); i++)
	{
		for (int j = 1; j <= 2; j++)
		{
			if (adjoint_vector[i][j] == szukana_nazwa)
			{
				return i;
			}

		}
	}

	return -1;
}

void Graph::glue_edges_in_adjoint_verticle()
{
	int licznik = 0;
	int i = 0;
	std::string to_co_zmieniam;

	for (auto wierzcholek : all_verticles)
	{
		auto nastepniki = wierzcholek.Get_next_neighbours();

			for (auto nastepnik_wierzcholka : nastepniki)
			{
				if (nastepnik_wierzcholka == "")//zabezpieczenie przed wierzcholkami izolowanymi 
				{
					break;
				}

				//szukam w wektorze po imieniu nastepnika aby polaczyc jego wejscie z wyjsciem wierzcholka ktory jest jego poprzednikiem
				i = szukanie_w_wektorze_po_nazwie(nastepnik_wierzcholka); // znalazlam wejscie i wyjscie tego nastepnika

				to_co_zmieniam = adjoint_vector[i][1];
				adjoint_vector[i][1] = adjoint_vector[licznik][2]; //lacze wejscie tego nastepnika z wyjsciem wierzcholka
																   //moge robic to po liczniku bo reprezentuje on na ktorym wierzcholku teraz operujemy

				//teraz musze wszystkie wystapienia liczby ktora byla na wejsciu nastepnika zamienic na wyjscie wierzcholka
				i = szukanie_w_wektorze_wejscia_i_wyjscia(to_co_zmieniam);

				while (i != -1)
				{
					if (to_co_zmieniam == adjoint_vector[licznik][2]) //nie chce zmieniac X na X bo to infinite loop
					{
						break;
					}

					else
					{
						if (adjoint_vector[i][1] == to_co_zmieniam)
						{
							adjoint_vector[i][1] = adjoint_vector[licznik][2];
						}

						if (adjoint_vector[i][2] == to_co_zmieniam)
						{
							adjoint_vector[i][2] = adjoint_vector[licznik][2];
						}

						i = szukanie_w_wektorze_wejscia_i_wyjscia(to_co_zmieniam);
					}

				}
			}
		

		

		licznik++;
	}
}

void Graph::create_oryginal_next_neighbours_map()
{
	std::string klucz;
	std::string element;
	std::string to_co_w_mapie;

	for (int i = 0; i<adjoint_vector.size(); i++)
	{
		klucz = adjoint_vector[i][1];
		element = adjoint_vector[i][2];
		
		if (adjoint_map.find(element) == adjoint_map.end()) //Jesli nie istnieje na mapie ten element to w ten sposob dodam wierzcholek izolowany jako klucz.  
															//Najpierw dodadza sie tez nieizolowane, ale one beda potem edytowane a izolowany juz nie i zostanie tu
		{
			adjoint_map[element] = ">";
			
		}

		element += "|";

		if (adjoint_map.find(klucz) != adjoint_map.end()) //czyli jesli juz mamy w mapie element o tym kluczu
		{
			to_co_w_mapie = adjoint_map[klucz];
			to_co_w_mapie += element; //to powiekszamy to co w mapie o ten element
			adjoint_map[klucz] = to_co_w_mapie;
		}

		if (adjoint_map.find(klucz) == adjoint_map.end()) //nie mamy w mapie elementu o tym kluczu
		{
			adjoint_map[klucz] = ">" + element;
		}

	}
}

void Graph::preparing_graph()
{
	generate_prev_neighbours_map_for_graph();
	Create_unordered_set_for_each_verticle();
	
}

void Graph::create_oryginal_graph()
{
	create_helper_vector();
	glue_edges_in_adjoint_verticle();
	create_oryginal_next_neighbours_map();
}

std::unordered_map<std::string, std::string> Graph::Get_adjoint_map()
{
	return adjoint_map;
}
