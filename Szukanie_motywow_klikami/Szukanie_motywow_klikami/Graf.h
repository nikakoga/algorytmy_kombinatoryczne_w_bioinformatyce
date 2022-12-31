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


	void dodawanie_wierzcholkow_do_grafu(std::unordered_map<int, Wierzcholek*> wierzcholki_w_tej_sekwencji)
	{
		for (unsigned int i = 1; i <= wierzcholki_w_tej_sekwencji.size(); i++)
		{
			Wierzcholek* ktory_dodaje_do_grafu = wierzcholki_w_tej_sekwencji[i];
			wszystkie_wierzcholki.insert({ next_free_ID, ktory_dodaje_do_grafu });
			next_free_ID++;
		}

	}

};

