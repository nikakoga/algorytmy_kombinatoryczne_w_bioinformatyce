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

				if (element.second[i]->get_sasiedzi().size() >= ILOSC_SEKWENCJI_W_PLIKU-1)
					//jesli wierzcholek i ma 4 lub wiecej sasiadow to moze wchodzic w sklad rozwiazania. 
				{
					szukaj_gwiazdy(element.second[i]); // szukam gwiazdy na takim wierzcholku
				}
			}
		}
	}

	void szukaj_gwiazdy(Wierzcholek * wierzcholek)
	{
		auto ID_sasiadow = wierzcholek->get_sasiedzi();
		std::unordered_set<int> objete_sekwencje;
		int nr_aktualnej_sekwencji;
		// TO DO
		std::unordered_map<int,std::unordered_set<int>> mapa_sasiadow_wg_sekwencji_z_ktorej_sa; // klucz to nr sekwencji

		for (auto ID_sasiada : ID_sasiadow)
		{
			nr_aktualnej_sekwencji = wszystkie_wierzcholki[ID_sasiada]->get_nr_sek(); //biore ID sasiada
			

			if (mapa_sasiadow_wg_sekwencji_z_ktorej_sa.find(nr_aktualnej_sekwencji) == mapa_sasiadow_wg_sekwencji_z_ktorej_sa.end()) //jesli jeszcze nie ma go w secie objetych sekwencji
			{
				objete_sekwencje.insert(ID_sasiada); //dodaje sasiada do unordered set
				mapa_sasiadow_wg_sekwencji_z_ktorej_sa.insert({ nr_aktualnej_sekwencji, objete_sekwencje }); //dodaje ten unordered_set
				objete_sekwencje.erase(objete_sekwencje.begin(), objete_sekwencje.end());//kasuje ten set zeby byl pusty
			}
			else //czyli jesli juz jest ta sekwencja w mapie
			{
				objete_sekwencje = mapa_sasiadow_wg_sekwencji_z_ktorej_sa[nr_aktualnej_sekwencji];
				objete_sekwencje.insert(ID_sasiada); //dodaje ze wierzcholek o tym ID tez pochodzi z tej sekwencji
				mapa_sasiadow_wg_sekwencji_z_ktorej_sa[nr_aktualnej_sekwencji] = objete_sekwencje; // dodaje do mapy uaktualniony spis wierzcholkow z tej sekwencji
				objete_sekwencje.erase(objete_sekwencje.begin(), objete_sekwencje.end());//kasuje ten set zeby byl pusty

			}

		}

		if (mapa_sasiadow_wg_sekwencji_z_ktorej_sa.size() == ILOSC_SEKWENCJI_W_PLIKU-1)//jesli jest co najmniej po 1 wierzcholku z kazdej sekwencji. -1 bo zaden sasiad nie moze byc z tej samej sekwencji co wierzcholek centralny, czyli do sprawdzenia mamy tylko czy istnieja sasiedzi z pozostalych sekwencji
		{ //jesli tu weszlam to istnieje gwiazda z tych sasiadow

			if (ID_sasiadow.size() == ILOSC_SEKWENCJI_W_PLIKU-1) //jesli ten wierzcholek generalnie ma tylko te 4 sasiadow a przeciez kazdy jest z innej sekwencji to jest jedyna opcja gwiazdy jaka mozemy miec
			{
				
				//mapa_gwiazd.insert({ wierzcholek->get_ID(), wierzcholek }); //dodaje ta gwiazde do mapy
				// licze jego punkty_gestosci
				// jesli jego punkty gestosci wynosza kombinacje z (l.wierzcholkow po 2 ) to mam juz klike i koncze dzialanie algo
			}

			if (ID_sasiadow.size() > ILOSC_SEKWENCJI_W_PLIKU - 1)//jesli ten wierzcholek ma wiecej niz 4 sasiadow to znaczy ze z tym wierzcholkiem jako centralnym mozna wygenerowac wiecej niz jedna opcje gwiazdy
			{
				//tutaj musisz teraz jakos ladnie trzymac wierzcholki z tych samych sekwencji tak aby te z tych samych mozna bylo wylosowac ktore sie wybierze do gwiazdy
				//np mamy wierzcholki z sekwencji : 1, 2 , 2 , 2, 3 , 4, 5
				//bierzemy 1,3,4,5 i losujemy 2 (robimy tak wiele razy zeby miec pewnosc ze powstaly rozwiazania wszystkie)
				//liczymy dla kazdej wygenerwanej tak gwiazdy punkty gestosci 
				//zapamietujemy te gwiazde jesli ma wieksze punkty gestosci niz dotychczas 
			}
				
		}
		
	}

	int licz_punkty_gestosci(std::vector<int> ID_reszty_gwiazdy)
	{
		int licznik = 0;
		for (int i = 0; i < ID_reszty_gwiazdy.size(); i++)
		{
			for (int j = i + 1; j < ID_reszty_gwiazdy.size(); j++)
			{
				if (wszystkie_wierzcholki[i]->get_sasiedzi().count(ID_reszty_gwiazdy[j]) == 1) //jesli wierzcholek ma w sasiadach inny wierzcholek wchodzacy w sklad gwiazdy
				{
					licznik++;
				}
			}
		}

		return licznik;
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
	
	void wyswietl_rozwiazanie()
	{
		std::unordered_set<int> sasiedzi;

		for (auto& [ID, wierzcholek] : mapa_gwiazd)
		{
			std::cout << "ID wierzcholka: " << ID << " Nr sekwencji: " << wierzcholek->get_nr_sek() << " Pozycja w sekwencji oryginalnej: " << wierzcholek->get_nr_org_nt() << " Podciag: " << wierzcholek->get_podciag()<<"\n";
			sasiedzi = wierzcholek->get_sasiedzi();

			for (auto ID_sasiada : sasiedzi)
			{
				std::cout << "ID wierzcholka: " << ID_sasiada << " Nr sekwencji: " << wszystkie_wierzcholki[ID_sasiada]->get_nr_sek() << " Pozycja w sekwencji oryginalnej: " << wszystkie_wierzcholki[ID_sasiada]->get_nr_org_nt() << " Podciag: " << wszystkie_wierzcholki[ID_sasiada]->get_podciag()<<"\n";
				
			}

			std::cout << "\n";
		}
	}

	void sprawdzam_dla_Nomika(int A)
	{
		std::cout << "Nr sekwencji: " << wszystkie_wierzcholki[A]->get_nr_sek() << " Pozycja sekwencji: " << wszystkie_wierzcholki[A]->get_nr_org_nt() << " Podciag: " << wszystkie_wierzcholki[A]->get_podciag() << "\n";
		std::cout << "sasiedzi: \n";
		auto sasiedzi = wszystkie_wierzcholki[A]->get_sasiedzi();

		for (auto sasiad : sasiedzi)
		{
			std::cout << "Nr sekwencji: " << wszystkie_wierzcholki[sasiad]->get_nr_sek() << " Pozycja sekwencji: " << wszystkie_wierzcholki[sasiad]->get_nr_org_nt() << " Podciag: " << wszystkie_wierzcholki[sasiad]->get_podciag() << "\n";
		}

		std::cout << "\n";
	}

};

