#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>


class Verticle
{
	std::string name;
	std::unordered_set <std::string> verticle_next_neighbours;
	std::unordered_set <std::string> verticle_prev_neighbours;

public:

	void Set_name (std::string signature)
	{
		name = signature;
	}

	std::string Get_name()
	{
		return name;
	}

	std::unordered_set <std::string>  Get_next_neighbours()
	{
		return verticle_next_neighbours;
	}

	std::unordered_set <std::string>  Get_prev_neighbours()
	{
		return verticle_prev_neighbours;
	}

	Verticle(std::string line_from_file)
	{
		std::stringstream line(line_from_file);

		std::string str_name;
		std::getline(line, str_name, '>');

		Set_name(str_name);

		std::string str_neighbour;

		while (!line.eof())
		{
			std::getline(line, str_neighbour, '|');

			if (std::find(verticle_next_neighbours.begin(), verticle_next_neighbours.end(), str_neighbour) != verticle_next_neighbours.end())
			{
				throw std::invalid_argument("Graf nie jest sprzezony");
			}

			verticle_next_neighbours.emplace(str_neighbour); 
			
		}
	}

	std::string generate_next_neighbour_list_for_verticle()
	{
		std::string list;

		list += name + ">";

		auto size = verticle_next_neighbours.size();
		
		unsigned int licznik = 0;
		for (auto element : verticle_next_neighbours)
		{
			list += element;
			licznik++;

			if (licznik < size)
			{
				list += "|";
			}
		}

		list += "\n";

		return list;
	}

	std::string generate_prev_neighbour_list_for_verticle()
	{
		std::string list;

		list += name + ">";

		auto size = verticle_prev_neighbours.size();

		unsigned int licznik = 0;
		for (auto element : verticle_prev_neighbours)
		{
			list += element;
			licznik++;

			if (licznik < size)
			{
				list += "|";
			}
		}

		list += "\n";

		return list;
	}
	
	bool is_verticle_adjoint(Verticle wierzcholek)
	{
		if (verticle_next_neighbours == wierzcholek.Get_next_neighbours()) //jesli sa takie same to moga byc sprzezone
		{
			return true;
		}

		if (is_there_any_common_neighbour_between_two_verticles(wierzcholek)) //tutaj sa tylko czesciowo takie same wiec nie moga byc sprzezone
		{
			 return false;
		}
				
		return true; //tutaj nie maja czesci wspolnej wcale wiec moga byc sprzezone
	}

	void Set_prev_neighbour(std::string str_prev_neigh) 
	{
		verticle_prev_neighbours.emplace(str_prev_neigh);
	}

private:
	bool is_there_any_common_neighbour_between_two_verticles(Verticle wierzcholek_A)
	{
		for (auto element : verticle_next_neighbours)
		{
			if (wierzcholek_A.Get_next_neighbours().count(element) > 0) //funkcja count zwraca 1 jesli badany element jest obecny w unordered set
			{
				// czyli jesli okaze sie ze wierzcholek_A na swojej liscie wierzcholkow
				// ma cos co nalezy rowniez do listy wierzcholkow tego obiektu to funkcja zwroci prawde
				return true;
			}
		}
		return false;
	}
};


