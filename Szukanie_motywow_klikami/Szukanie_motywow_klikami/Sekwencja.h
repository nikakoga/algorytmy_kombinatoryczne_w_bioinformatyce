#pragma once
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "Wierzcholek.h"

int ID_wierzcholka = 1; //ZMIENNA GLOBALNA !

class Sekwencja
{
	int numer_sekwencji;
	std::string ID; 
	std::unordered_map<int, char> wiarygodne_nukleotydy;
	std::unordered_map<int, char> niewiarygodne_nukleotydy;
	//krotka ktora bedzie trzymac nr oryginalnego nt, nr wiarygodnego nt i podciag
	std::unordered_map<int, Wierzcholek*> wierzcholki_w_tej_sekwencji;
	//std::unordered_map<int, std::string> podciag; //klucz to nt w oryginale od ktorego sie podciag zaczyna 
	
public: 
	Sekwencja(int numer, std::string sekwencja)
	{
		numer_sekwencji = numer;

		std::stringstream cala_sekwencja (sekwencja);
		std::string first_line;
		getline(cala_sekwencja,first_line);
		std::stringstream line (first_line);

		std::string zbedny_znak;
		std::string nazwa;
		std::getline(line, zbedny_znak, '>');//zeby w nazwie bylo bez ">"
		std::getline(line, nazwa, ' '); //zeby pobrac tylko nazwe z calego wersu nazwy i zbednych rzeczy

		ID = nazwa;

		std::string czesc_sekwencji;
		int ilosc_wczytanych_nukleotydow = 0;
		int nr_nukleotydu = 1;

		 
		while (!cala_sekwencja.eof())
		{
			std::getline(cala_sekwencja, czesc_sekwencji);
			ilosc_wczytanych_nukleotydow = czesc_sekwencji.size();

			for (int i = 0; i < ilosc_wczytanych_nukleotydow; i++)
			{
				wiarygodne_nukleotydy[nr_nukleotydu] = czesc_sekwencji[i]; //czesc_sekwencji w kazdej petli jest nadpisywana, ale nr nukleotydu jest ciagle aktualizowany i dzieki temu czytam calosc
				nr_nukleotydu++;
			}

		}
		
	}

	void uwzglednianie_progu_wiarygodnosci(std::string wiarygodnosc, int zadany_prog) //dodaje do klasy Sekwencja mape wiarygodnych i niewiarygodnych nt
	{
		std::stringstream cala_wiarygodnosc(wiarygodnosc);
		std::string smieci;
		getline(cala_wiarygodnosc, smieci);
		int nr_nukleotydu_w_oryginale = 1;
		int nr_nt_wiarygodnego;
		int prev_nr_nt_wiarygodnego = 0;
		int ilosc_usunietych_nt = 0;

		std::string linia;
		std::string wiarygodnosc_jednego_nukleotydu;
		

		while (!cala_wiarygodnosc.eof())
		{
			getline(cala_wiarygodnosc, linia);
			std::stringstream stream_linii(linia);
			while (!stream_linii.eof())
			{
				getline(stream_linii, wiarygodnosc_jednego_nukleotydu, ' ');
				int wiarygodnosc = std::stoi(wiarygodnosc_jednego_nukleotydu);
				if (wiarygodnosc < zadany_prog)
				{
					ilosc_usunietych_nt++;
					niewiarygodne_nukleotydy[nr_nukleotydu_w_oryginale] = wiarygodne_nukleotydy[nr_nukleotydu_w_oryginale]; //mozliwe ze nie uzyje ale moze sie przydac przy debugowanu
					wiarygodne_nukleotydy.erase(nr_nukleotydu_w_oryginale); // to tez
						
				}
				nr_nt_wiarygodnego = nr_nukleotydu_w_oryginale - ilosc_usunietych_nt; //pozycja jaka mialby nt po usunieciu niewiarygodnych

				if (nr_nt_wiarygodnego > 0 && nr_nt_wiarygodnego != prev_nr_nt_wiarygodnego) // >0 aby nie dodac nt nr 1 jesli bylby niewiarygodny
					//gdy zwiekszy sie liczba nukleotydow_w_oryginale ale nie zwiekszy sie liczba nukleotydow_wiarygodnych to byl niewiarygodny nukleotyd
					// gdy zwiekszy sie liczba nukleotydow_w_oryginale i zwiekszy_sie_liczba nt_wiarygodnych to ten nukleotyd ktory wlasnie przejrzalam jest wiarygodny
					// prev_wiarygodny pozwala mi sledzic zmiany czy przybylo wiarygodnego_nt
				{
					Wierzcholek aktualny(nr_nukleotydu_w_oryginale, nr_nt_wiarygodnego,ID_wierzcholka);
					prev_nr_nt_wiarygodnego = nr_nt_wiarygodnego;
					Wierzcholek* wskaznik_na_aktualny = &aktualny;
					wierzcholki_w_tej_sekwencji.insert({ ID_wierzcholka,wskaznik_na_aktualny });
					ID_wierzcholka++; //aktualizuje zmienna globalna. Graf sklada sie z wszystkich wierzcholkow z wszystkich sekwencji a ja chce aby kazdy wierzcholek mial unikatowe ID wiec musi byc globalnie
				}
			
				nr_nukleotydu_w_oryginale++;

			}

		}
	}

	void dodawanie_wierzcholkow_do_grafu(/*tu podasz graf*/)
	{

	}
};

