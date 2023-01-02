#pragma once
#include <string>
#include <vector>
#include <iostream>

class Wierzcholek
{
	std::string podciag;
	int nr_sekwencji;
	int pozycja_w_oryginalnej_sekwencji;
	int numer_po_usunieciu_niewiarygodnych;
	int ID;
	std::vector<Wierzcholek*> somsiedzi;
	std::vector<int> ID_somsiadow;

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

	int get_ID()
	{
		return ID;
	}

	std::string get_podciag()
	{
		return podciag;
	}

	int ger_nr_sek()
	{
		return nr_sekwencji;
	}
};

