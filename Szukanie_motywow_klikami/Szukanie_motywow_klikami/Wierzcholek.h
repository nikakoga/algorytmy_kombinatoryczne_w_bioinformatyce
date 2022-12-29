#pragma once
#include <string>
#include <vector>

class Wierzcholek
{
	std::string podciag;
	int pozycja_w_oryginalnej_sekwencji;
	int numer_po_usunieciu_niewiarygodnych;
	int ID;
	std::vector<Wierzcholek*> somsiedzi;
	std::vector<int> ID_somsiadow;

public:
	Wierzcholek(int numer_w_oryginalnej_sekwencji, int nr_po_usunieciu_niewiarygodnych)
	{
		pozycja_w_oryginalnej_sekwencji = numer_w_oryginalnej_sekwencji;
		numer_po_usunieciu_niewiarygodnych = nr_po_usunieciu_niewiarygodnych;
		
	}

	void set_podciag(std::string sek)
	{
		podciag = sek;
	}

	void set_ID(int id)
	{
		ID = id;
	}

};

