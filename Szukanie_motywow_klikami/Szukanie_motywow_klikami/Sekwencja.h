#pragma once
#include <map>
#include <fstream>
#include <sstream>
#include "Graf.h"


class Sekwencja
{
	int numer_sekwencji;
	std::string ID; 
	int dlugosc_podciagu;
	std::unordered_map<int, char> wiarygodne_nukleotydy;
	std::unordered_map<int, char> niewiarygodne_nukleotydy;
	int ilosc_nukleotydow_w_sekwencji;
	std::string sekwencja_wiarygodnych_nukleotydow;
	//krotka ktora bedzie trzymac nr oryginalnego nt, nr wiarygodnego nt i podciag
	std::unordered_map<int, Wierzcholek*> wierzcholki_w_tej_sekwencji;
	//std::unordered_map<int, std::string> podciag; //klucz to nt w oryginale od ktorego sie podciag zaczyna 
	
public: 
	Sekwencja(int numer, std::string sekwencja,int wybrana_dlugosc_podciagu)
	{
		numer_sekwencji = numer;
		dlugosc_podciagu = wybrana_dlugosc_podciagu;

		std::stringstream cala_sekwencja (sekwencja);
		std::string first_line;
		std::getline(cala_sekwencja,first_line);
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
		ilosc_nukleotydow_w_sekwencji += nr_nukleotydu-1;//bo nr_nt jest teraz wolny, gotowy do zapisania tam nowego nt, czyli nie ma nt o takim numerze
		
	}

	void uwzglednianie_progu_wiarygodnosci(std::string wiarygodnosc, int zadany_prog) //dodaje do klasy Sekwencja mape wiarygodnych i niewiarygodnych nt, tworzy wstepnie wierzcholki
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
				if (wiarygodnosc_jednego_nukleotydu == "") //pusty string pobierze sie na koncu sekwencji, trzeba wyjsc wtedy z petli
				{
					break;
				}
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
					Wierzcholek* wskaznik_na_aktualny = new Wierzcholek(nr_nukleotydu_w_oryginale, nr_nt_wiarygodnego, numer_sekwencji);
					prev_nr_nt_wiarygodnego = nr_nt_wiarygodnego;
					wierzcholki_w_tej_sekwencji.insert({ nr_nt_wiarygodnego,wskaznik_na_aktualny });
					//tych wierzcholkow tworzy sie tutaj za duzo bo kazdy nukleotyd jest wierzcholkiem na razie a w finale kazdy podciag nim bedzie. Pozniej usune z wierzcholkow te nt ktore sa na samym koncu sekwencji  inie aczyna sie z nich juz zaden podciag
					
				}
			
				nr_nukleotydu_w_oryginale++;

			}

		}

	}

	void tworzenie_stringa_z_sekwencja_wiarygodnych_nt()
	{
		std::string sekwencja;
		for (int i = 1; i <= ilosc_nukleotydow_w_sekwencji; i++)
		{
			if (wiarygodne_nukleotydy.find(i) != wiarygodne_nukleotydy.end()) //jesli nukleotyd o oryginalnym numerze i jest w mapie wiarygodnych nt
			{
				sekwencja += wiarygodne_nukleotydy[i]; //dodaje go do sekwencji
			}
		}
		sekwencja_wiarygodnych_nukleotydow = sekwencja;
	}

	std::unordered_map<int, Wierzcholek*> tworzenie_podciagow()
	{
		tworzenie_stringa_z_sekwencja_wiarygodnych_nt();
		std::string podciag;
		unsigned int i;
		int licznik;
		int pozycja_do_dodania;

		for (i = 1; i <= sekwencja_wiarygodnych_nukleotydow.length() - dlugosc_podciagu +1 ; i++) //od 1 wiarygodnego nt lece ramka o dlugosci podciagu i dodaje wszystkie nt ktore sie w niej mieszcza
		{
			pozycja_do_dodania = i - 1;
			licznik = 0;
			while (licznik < dlugosc_podciagu)
			{
				podciag += sekwencja_wiarygodnych_nukleotydow[pozycja_do_dodania];
				pozycja_do_dodania++;
				licznik++;
			}

			auto w_ktorym_dodaje_podciag = wierzcholki_w_tej_sekwencji[i]; //TO DO TUTAJ CHYBA PRZPISUJESZ WSKAZNIK POD WSKAZNIK
			w_ktorym_dodaje_podciag->set_podciag(podciag);
			podciag = ""; //kasuje podciag zeby dodac nowy 
		
		}
	
		int rozmiar_ze_zbednymi_wierzcholkami = wierzcholki_w_tej_sekwencji.size();
		for (i; i <= rozmiar_ze_zbednymi_wierzcholkami; i++) //teraz musze usun¹æ z mapy wierzcho³ków nukleotydy od których nie zaczyna siê ¿aden podci¹ bo one jednak nie bêd¹ wierzcho³kami
		{
			Wierzcholek* do_zwolnienia_wskaznik = wierzcholki_w_tej_sekwencji[i];
			wierzcholki_w_tej_sekwencji.erase(i); //mapa ma teraz tylko te wierzcholki ktore bede chciala dodac do grafu bo maja podciagi
			delete do_zwolnienia_wskaznik; //zwalniam pamiec 
			
		}

		return wierzcholki_w_tej_sekwencji;

		
	}


	
};

