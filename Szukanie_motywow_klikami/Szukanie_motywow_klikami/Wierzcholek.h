#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

#define ILOSC_PLIKOW 1
#define ILOSC_SEKWENCJI_W_PLIKU 5
#define ILE_RAZY_LOSUJE_GWIAZDE 10

class Wierzcholek
{
	std::string podciag;
	int nr_sekwencji;
	int pozycja_w_oryginalnej_sekwencji;
	int numer_po_usunieciu_niewiarygodnych;
	int ID;
	std::unordered_set<int> sasiedzi; //dodaje tutaj ich ID


public:

	Wierzcholek(int numer_w_oryginalnej_sekwencji, int nr_po_usunieciu_niewiarygodnych, int nr_seq)
	{
		pozycja_w_oryginalnej_sekwencji = numer_w_oryginalnej_sekwencji;
		numer_po_usunieciu_niewiarygodnych = nr_po_usunieciu_niewiarygodnych;
		nr_sekwencji = nr_seq;
		
	}

	void set_podciag(std::string sek)
	{
		podciag = sek;
	}
	void set_ID(int id)
	{
		ID = id;
	}

	void dodaj_sasiada(int ID_sasiada)
	{
		sasiedzi.insert(ID_sasiada);
	}

	int get_ID()
	{
		return ID;
	}
	std::string get_podciag()
	{
		return podciag;
	}
	int get_nr_sek()
	{
		return nr_sekwencji;
	}
	int get_nr_nt()
	{
		return numer_po_usunieciu_niewiarygodnych;
	}
	int get_nr_org_nt()
	{
		return pozycja_w_oryginalnej_sekwencji;
	}
	std::unordered_set<int> get_sasiedzi()
	{
		return sasiedzi;
	}

	void wyswietl_sasiadow()
	{
		for (auto sasiad : sasiedzi)
		{
			std::cout << sasiad << " ";
		}
	}
};

