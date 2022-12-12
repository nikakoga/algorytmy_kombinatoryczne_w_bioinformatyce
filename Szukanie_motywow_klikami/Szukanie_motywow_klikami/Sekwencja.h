#pragma once
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>

class Sekwencja
{
	std::string ID; 
	std::unordered_map<int, char> wiarygodne_nukleotydy;
	std::unordered_map<int, char> niewiarygodne_nukleotydy;
	std::unordered_map<int, std::string> podciag; //klucz to nt od ktorego sie podciag zaczyna

public: 
	Sekwencja(std::fstream& f_sekwencja)
	{
		std::string first_line;
		getline(f_sekwencja,first_line);
		std::stringstream line (first_line);

		std::string nazwa;
		std::getline(line, nazwa, ' '); //zeby pobrac tylko nazwe z calego wersu nazwy + zbednych rzeczy

		ID = nazwa;

		std::string czesc_sekwencji;
		int ilosc_wczytanych_nukleotydow = 0;
		int nr_nukleotydu = 1;

		 
		while (!f_sekwencja.eof())
		{
			std::getline(f_sekwencja, czesc_sekwencji);
			ilosc_wczytanych_nukleotydow = czesc_sekwencji.size();

			for (int i = 0; i < ilosc_wczytanych_nukleotydow; i++)
			{
				wiarygodne_nukleotydy[nr_nukleotydu] = czesc_sekwencji[i];
				nr_nukleotydu++;
			}

		}
		
	}

	void uwzglednianie_progu_wiarygodnosci(std::fstream& f_wiarygodnosc, int zadany_prog)
	{
		std::string smieci;
		getline(f_wiarygodnosc, smieci);
		int nr_nukleotydu = 1;

		std::string linia;
		std::string wiarygodnosc_jednego_nukleotydu;
		

		while (!f_wiarygodnosc.eof())
		{
			getline(f_wiarygodnosc, linia);
			std::stringstream stream_linii(linia);
			while (!stream_linii.eof())
			{
				getline(stream_linii, wiarygodnosc_jednego_nukleotydu, ' ');
				int wiarygodnosc = std::stoi(wiarygodnosc_jednego_nukleotydu);
				if (wiarygodnosc < zadany_prog)
				{
					niewiarygodne_nukleotydy[nr_nukleotydu] = wiarygodne_nukleotydy[nr_nukleotydu];
					wiarygodne_nukleotydy.erase(nr_nukleotydu); 
					
				}
				nr_nukleotydu++;

			}

		}
	}
};

