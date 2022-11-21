#include "Verticle.h"

void Verticle::Set_name(std::string signature)
{
	name = signature;
}

std::string Verticle::Get_name()
{
	return name;
}

std::unordered_set<std::string> Verticle::Get_next_neighbours()
{
	return verticle_next_neighbours;
}

std::unordered_set<std::string> Verticle::Get_prev_neighbours()
{
	return verticle_prev_neighbours;
}

void Verticle::Show_prev_neighbours()
{
	for (auto element : verticle_prev_neighbours)
	{
		std::cout << element << " ";
	}
	std::cout << "\n";
}

Verticle::Verticle(std::string line_from_file)
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
			throw std::invalid_argument("Graf nie jest sprzezony bo jest multigrafem");
		}

		verticle_next_neighbours.emplace(str_neighbour);

	}
}

std::string Verticle::generate_next_neighbour_list_for_verticle()
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

std::string Verticle::generate_prev_neighbour_list_for_verticle()
{
	std::string list;

	list += name + "<";

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

Result Verticle::is_verticle_adjoint(Verticle wierzcholek)
{
	if (verticle_next_neighbours == wierzcholek.Get_next_neighbours()) //jesli sa takie same to moga byc sprzezone
	{
		return Do_sprawdzenia_czy_liniowy; // po to aby potem wlasnie dla tej pary wierzcholkow sprawdzac czy maja wspolonych poprzednikow bo jesli maja to graf nie bedzie liniowy
	}

	if (is_there_any_common_next_neighbour_between_two_verticles(wierzcholek)) //tutaj sa tylko czesciowo takie same wiec nie moga byc sprzezone
	{
		return Czesc_wspolnych_nastepnikow;
	}

	return Liniowy; //tutaj nie maja czesci wspolnej wcale wiec moga byc sprzezone i moze byc liniowy nawet jesli ma poprzedniki te same
}

void Verticle::Set_prev_neighbour(std::string str_prev_neigh)
{
	verticle_prev_neighbours.emplace(str_prev_neigh);
}

bool Verticle::is_there_any_common_next_neighbour_between_two_verticles(Verticle wierzcholek_A)
{
	return is_there_any_common_neighbours(verticle_next_neighbours, wierzcholek_A.Get_next_neighbours());
}

bool Verticle::is_there_any_common_prev_neighbour_between_two_verticle(Verticle wierzcholek_A)
{
	return is_there_any_common_neighbours(verticle_prev_neighbours, wierzcholek_A.Get_prev_neighbours());
}

bool Verticle::is_there_any_common_neighbours(std::unordered_set<std::string> neighbours, std::unordered_set<std::string> neighboursToCompare)
{
	for (auto element : neighbours)
	{
		if (neighboursToCompare.count(element) > 0) //funkcja count zwraca 1 jesli badany element jest obecny w unordered set
		{
			// czyli jesli okaze sie ze wierzcholek_A na swojej liscie wierzcholkow
			// ma cos co nalezy rowniez do listy wierzcholkow tego obiektu to funkcja zwroci prawde
			return true;
		}
	}
	return false;
}
