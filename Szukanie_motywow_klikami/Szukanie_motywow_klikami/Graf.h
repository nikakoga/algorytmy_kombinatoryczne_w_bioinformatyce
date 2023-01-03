#pragma once
#include <unordered_map>
#include <cstdlib>
#include "Wierzcholek.h"


class Graf
{
	int next_free_ID;
	int dlugosc_podciagu;
	std::unordered_map<int, Wierzcholek*> wszystkie_wierzcholki; //klucz to unikalne ID wierzcholka (rozdaje po kolei)
	std::unordered_map<std::string, std::vector<Wierzcholek*>> mapa_podciagow;
	std::unordered_map<int, Wierzcholek*> mapa_gwiazd;
	std::vector<int> gwiazda;

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

	void ustalanie_sasiedztwa()
	{
		int rozmiar;
		for (auto element : mapa_podciagow)
		{
			rozmiar = element.second.size(); //element.second to wektor z wskaznikami na wierzcholki ktore maja ten podciag
			for (int i = 0; i < rozmiar;i++) //iteruje po wierzcholkach ktore maja ten podciag
			{
				for (int j = i + 1; j < rozmiar; j++)
				{

					if (element.second[i]->get_nr_sek() != element.second[j]->get_nr_sek()) //jesli te wierzcholki sa z roznych sekwencji
					{
						if (std::abs(element.second[i]->get_nr_nt() - element.second[j]->get_nr_nt()) <= 10 * dlugosc_podciagu)
							// jesli wartosc bezwzgledna z wyniku odejmowania nr_nt tych sekwencji jest mniejsza lub rowna 10*dlugosc podciagu to sa to sasiedzi
						{
							element.second[i]->dodaj_sasiada(element.second[j]->get_ID()); // j jest sasiadem i
							element.second[j]->dodaj_sasiada(element.second[i]->get_ID()); // i jest sasiadem j 
						}

					}
				}

				if (element.second[i]->get_sasiedzi().size() >= ILOSC_SEKWENCJI_W_PLIKU)
					//jesli wierzcholek i ma 4 lub wiecej sasiadow to moze wchodzic w sklad rozwiazania. 
					//Poniewaz ja do "sasiadow" dodalam tez ten aktualny wierzcholek (aby latwiej porownywac hashsety) to rozmiar sasiadow musi wynosic 5 lub wiecej aby dany wierzcholek mogl wchodzic w sklad rozwiazania
				{
					mapa_gwiazd.insert({ element.second[i]->get_ID() ,element.second[i]});
				}
			}
		}
	}

	void szukaj_gwiazdy()
	{
		
		
	}

	void set_dlugosc_podciagu(int dlugosc)
	{
		dlugosc_podciagu = dlugosc;
	}

	void wyswietl_wektor_wierzcholkow(std::vector<Wierzcholek*> wierzcholki)
	{
		for (auto wierzcholek : wierzcholki)
		{
			std::cout << wierzcholek->get_nr_sek()<<"->" << wierzcholek->get_ID() << " ";
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

	void wyswietl_mape_dla_konkretnego_podciagu(std::string klucz)
	{
		if (mapa_podciagow.find(klucz) != mapa_podciagow.end())
		{
			auto wektor_wskaznikow_na_wierzcholki = mapa_podciagow[klucz];

			for (auto wskaznik : wektor_wskaznikow_na_wierzcholki)
			{
				std::cout <<"sekwencja: "<<wskaznik->get_nr_sek()<<" nr nt w oryginale: "<<wskaznik->get_nr_org_nt() << " ID: " << wskaznik->get_ID() << " podciag: " << wskaznik->get_podciag() << "\n";
			}
			
		}
	}
	void wyswietl_kandydatow_do_gwiazdy()
	{
		std::cout << "KANDYDACI" << "\n";
		for (auto& [ID_kandydata, wierzcholek] : mapa_kandydatow_do_gwiazdy)
		{
			std::cout << ID_kandydata << "->";
			wierzcholek->wyswietl_sasiadow();
			std::cout<< "\n";
		}
		std::cout << "KONIEC";
	}

};

