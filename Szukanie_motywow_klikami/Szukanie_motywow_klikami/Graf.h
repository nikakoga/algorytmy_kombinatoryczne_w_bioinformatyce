#pragma once
#include <unordered_map>
#include "Wierzcholek.h"


class Graf
{
	//jakos przechowuj wierzcholki tak aby nie bylo to w wektorze
	//wierzcholki musisz polaczyc nieskierowanymi lukami jesli maja ten sam podciag ale sa z innych sekwencji i dl nt start nie jest wieksza niz dl_podciagu * 10
	int next_free_ID;
	std::unordered_map<int, Wierzcholek*> wszystkie_wierzcholki;
	std::vector<std::unordered_map<int, Wierzcholek*>> wektor_map_poszczegolnych_sekwencji; //mapy wszystkich nt ktore tworzylam w klasie sekwencja sa tutaj wpakowane do wektora (kazda sekwencja ma tu jedna mape)
	// w wektorze komorki sa numerowane od 0 wiec chcac sie dostac do mapy sekwencji 2 musze szukac w wektorze w komorce 2-1. Analogicznie do reszty
	std::unordered_map<std::string, std::vector<Wierzcholek*>> mapa_podciagow;

public:

	Graf(int ID_start)
	{
		next_free_ID = ID_start;
	}

	void dodawanie_do_mapy_podciagu( Wierzcholek* wierzcholek)
	{
		std::string podciag = wierzcholek->get_podciag();

		std::vector<Wierzcholek*> wektor_wierzcholkow;

		if (mapa_podciagow.find(podciag) == mapa_podciagow.end())//jesli nie mam takiego podciagu w mapie to dodaje go
		{
			wektor_wierzcholkow.push_back(wierzcholek);
			mapa_podciagow.insert({ podciag,wektor_wierzcholkow });
		}
		else //jesli juz mam taki podciag w mapie
		{
			wektor_wierzcholkow = mapa_podciagow[podciag]; //wyciagam do wektora te wierzcholki ktore juz tam sa
			wektor_wierzcholkow.push_back(wierzcholek); //dodaje ten nowy
			mapa_podciagow[podciag] = wektor_wierzcholkow; //wkladam uaktualnione do mapy
		}
	}

	void dodawanie_wierzcholkow_do_grafu(std::unordered_map<int, Wierzcholek*> wierzcholki_w_tej_sekwencji)
	{
		for (unsigned int i = 1; i <= wierzcholki_w_tej_sekwencji.size(); i++)
		{
			Wierzcholek* ktory_dodaje_do_grafu = wierzcholki_w_tej_sekwencji[i];
			wszystkie_wierzcholki.insert({ next_free_ID, ktory_dodaje_do_grafu });
			ktory_dodaje_do_grafu->set_ID(next_free_ID); //teraz ten wierzcholek tez ma informacje o tym jaki ma nr w grafie
			next_free_ID++;
			

			dodawanie_do_mapy_podciagu(ktory_dodaje_do_grafu); //tutaj, zeby nie iterowac bez sensu drugi raz po wszystkim w celu stworzenia mapy
			
		}

	}

	void dodawanie_mapy_sekwencji(std::unordered_map<int, Wierzcholek*> mapa)
	{
		wektor_map_poszczegolnych_sekwencji.push_back(mapa);
	}

	void dodawanie_informacji_do_grafu(std::unordered_map<int, Wierzcholek*> wierzcholki_w_tej_sekwencji)
	{
		dodawanie_wierzcholkow_do_grafu(wierzcholki_w_tej_sekwencji);
		dodawanie_mapy_sekwencji(wierzcholki_w_tej_sekwencji);
	}

	void wyswietl_wektor_wierzcholkow(std::vector<Wierzcholek*> wierzcholki)
	{
		for (auto wierzcholek : wierzcholki)
		{
			std::cout << wierzcholek->ger_nr_sek()<<"->" << wierzcholek->get_ID() << " ";
		}
	}
	void wyswietl_mape_podciagow()
	{
		for (auto element : mapa_podciagow)
		{
			std::cout << element.first << " ";
			wyswietl_wektor_wierzcholkow(element.second);
			std::cout<< "\n";
		}
	}

};

