#pragma once
#include <unordered_map>
class Graf
{
	//jakos przechowuj wierzcholki tak aby nie bylo to w wektorze
	//wierzcholki musisz polaczyc nieskierowanymi lukami jesli maja ten sam podciag ale sa z innych sekwencji i dl nt start nie jest wieksza niz dl_podciagu * 10
	std::unordered_map<int, Wierzcholek*> wszystkie_wierzcholki;

public:
	void add_to_graph(int ID, Wierzcholek* wierzcholek)
	{
		wszystkie_wierzcholki.insert({ ID,wierzcholek });
	}

};

