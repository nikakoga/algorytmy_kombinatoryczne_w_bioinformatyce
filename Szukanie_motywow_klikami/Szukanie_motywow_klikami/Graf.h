#pragma once
#include <unordered_map>
#include "Wierzcholek.h"


class Graf
{
	//jakos przechowuj wierzcholki tak aby nie bylo to w wektorze
	//wierzcholki musisz polaczyc nieskierowanymi lukami jesli maja ten sam podciag ale sa z innych sekwencji i dl nt start nie jest wieksza niz dl_podciagu * 10
	int next_free_ID;
	std::unordered_map<int, Wierzcholek*> wszystkie_wierzcholki;

public:

	Graf(int ID_start)
	{
		next_free_ID = ID_start;
	}

	void add_to_graph(int ID, Wierzcholek* wierzcholek)
	{
		wszystkie_wierzcholki.insert({ ID,wierzcholek });
	}

	int get_next_free_ID()
	{
		return next_free_ID;
	}

	void set_next_free_ID()
	{
		next_free_ID++;
	}

};

