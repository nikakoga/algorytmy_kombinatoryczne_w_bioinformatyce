#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include <algorithm>
#include <boost/filesystem.hpp>

bool Czy_mozna_stworzyc_mape(int liczba_elementow, std::map<int, int> mapa)
{
	if (mapa.find(liczba_elementow) != mapa.end()) // jesli istnieje taka wartosc w mapie
	{
		return true;
	}
	return false;
}

int najwiekszy_element(std::vector<int> fragmenty)
{
	int max = 0;

	for (int i = 0; i < fragmenty.size(); i++)
	{
		if (fragmenty[i] > max)
		{
			max = fragmenty[i];
		}
	}
	return max;
}

int drugi_najwiekszy_element(std::vector<int> fragmenty, int max)
{
	int drugi_max = 0;

	for (int i = 0; i < fragmenty.size(); i++)
	{
		if (fragmenty[i] > drugi_max && fragmenty[i] < max)
		{
			drugi_max = fragmenty[i];
		}
	}

	return drugi_max;
}

int szukaj_elementu(std::vector<int> fragmenty, int dlugosc)
{
	for (int i = 0; i < fragmenty.size(); i++)
	{
		if (fragmenty[i] == dlugosc)
		{
			return i;
		}
	}
	return -1;
}

std::vector<int> zeruj_wektor_uzyc(std::vector<int> uzyte)
{

	for (int i = 0; i < uzyte.size(); i++)
	{
		uzyte[i] = 0;
	}
	return uzyte;
}

double policz_czas(clock_t start)
{
	auto stop = clock();
	double czas_wykonywania_w_sekundach = (double)(stop - start) / (double)CLOCKS_PER_SEC;

	return czas_wykonywania_w_sekundach;
}

void wyswietl_mape(std::vector<int> *wskaznik_na_rozwiazanie)
{
	std::vector<int> rozwiazanie = *wskaznik_na_rozwiazanie;
	for (auto element : rozwiazanie)
	{
		std::cout << element << " ";
	}
}

int szukaj_elementu_jesli_jest_niewykorzystany(int wartosc, std::vector<int> uzyte, std::vector<int> pociete_fragmenty)
{
	for (int i = 0; i < pociete_fragmenty.size(); i++)
	{
		if (pociete_fragmenty[i] == wartosc)
		{
			if (uzyte[i] == 0) // sprawdzam czy ten element nie jest wykorzystany
			{
				return i;
			}
		}
	}

	return -1; // zwracam -1 jesli nie ma nieuzytego elementu o takiej wartosci
}

int get_okreslony_element_z_rozwiazania(std::vector<int> *wskaznik_na_rozwiazanie, int element)
{
	std::vector<int> rozwiazanie = *wskaznik_na_rozwiazanie;

	int wartosc = rozwiazanie[element];

	return wartosc;
}

void wyswietl_statusy_elementow(std::vector<int> pociete_fragmenty, std::vector<int> uzyte_w_tym_wywolaniu)
{
	for (int i = 0; i < pociete_fragmenty.size(); i++)
	{
		std::cout << pociete_fragmenty[i] << " status: " << uzyte_w_tym_wywolaniu[i] << "\n";
	}
}

void szukaj_rozwiazania(std::vector<int> *wskaznik_na_rozwiazanie, int max_ilosc_ciec, clock_t czas_start, std::vector<int> uzyte_w_obrebie_tego_wywolania, std::vector<int> pociete_fragmenty, bool *czy_znalzalam)
{
	// std::cout << "Ilosc elementow w rozwiazaniu: " << wskaznik_na_rozwiazanie->size();
	// std::cout << "\n";
	// std::cout << "Rozwiazanie ";
	// wyswietl_mape(wskaznik_na_rozwiazanie);
	// std::cout << "\n";
	if (wskaznik_na_rozwiazanie->size() == max_ilosc_ciec)
	{
		std::cout << "Znaleziono mape: ";
		wyswietl_mape(wskaznik_na_rozwiazanie);
		std::cout << "Czas szukania rozwiazania: " << policz_czas(czas_start) << "\n";
		*czy_znalzalam = true;
		return;
	}
	if (policz_czas(czas_start) >= 3600)
	{
		std::cout << "Przekroczono czas dla szukania rozwiaznania\nKoncze program";
		*czy_znalzalam = false;
		return;
	}

	else
	{
		// std::cout << "Zaczynam sprawdzanie opcji\n";
		for (int i = 0; i < uzyte_w_obrebie_tego_wywolania.size(); i++) // iteruje po tablicy uzyc fragmentow
		{
			std::vector<int> pozycje_zmienionych_elementow;
			// std::cout << pociete_fragmenty[i] << "status: " << uzyte_w_obrebie_tego_wywolania[i] << "\n";
			if (uzyte_w_obrebie_tego_wywolania[i] == 0) // jesli jeszcze nie uzylam tego fragmentu
			{
				wskaznik_na_rozwiazanie->push_back(pociete_fragmenty[i]); // dodaje go na probe do rozwiazania
				// std::cout << "dodaje na probe " << pociete_fragmenty[i] << "\n";
				int suma = pociete_fragmenty[i];
				bool czy_wszystko_sie_zgadzalo = true;

				for (int j = wskaznik_na_rozwiazanie->size() - 2; j >= 0; j--) // iteruje po elementach ktore sa w rozwiazaniu j zaczyna jako ostatni element
																			   //-1 tam jest ostatni element bo numeruje wektor od 0
				{
					suma += get_okreslony_element_z_rozwiazania(wskaznik_na_rozwiazanie, j);

					// std::cout << "suma do sprawdzenia: "<<suma<<"\n";
					int nr_elementu = szukaj_elementu_jesli_jest_niewykorzystany(suma, uzyte_w_obrebie_tego_wywolania, pociete_fragmenty);
					if (nr_elementu != -1) // gdy funkcja nie zwraca -1 to znalazla element o zadanej wartosci ktory jest nieuzyty
					{
						// std::cout << "obecny\n";
						uzyte_w_obrebie_tego_wywolania[nr_elementu] = 1; // jesli nie jest wykorzystany ustawiam ze teraz juz jest
						// std::cout << "status: " << uzyte_w_obrebie_tego_wywolania[nr_elementu];
						// std::cout<< "\n";
						pozycje_zmienionych_elementow.push_back(nr_elementu);
					}
					else if (nr_elementu == -1) // znaleziony element jest juz wykorzystany
					{
						// std::cout << "nieobecny lub juz uzyty\n";
						czy_wszystko_sie_zgadzalo = false;
						break;
					}
				}
				if (czy_wszystko_sie_zgadzalo == false)
				{
					wskaznik_na_rozwiazanie->pop_back(); // nie pasuje, usuwam to co dodalam
					// std::cout << "proba nie udana, element nie pasowal\n";
					// std::cout << "aktualne rozwiazanie: ";
					// wyswietl_mape(wskaznik_na_rozwiazanie);
					// std::cout << "\n";

					if (!pozycje_zmienionych_elementow.empty()) // jesli zdazylam cokolwiek zmienic w wektorze uzyc
					{
						// std::cout << "cofam pozycje zmienione" << '\n';
						for (int k = 0; k < pozycje_zmienionych_elementow.size(); k++)
						{
							int element_do_cofniecia = pozycje_zmienionych_elementow[k];
							uzyte_w_obrebie_tego_wywolania[element_do_cofniecia] = 0; // cofam na nieuzyte
																					  // std::cout << pociete_fragmenty[element_do_cofniecia] << "status: " << uzyte_w_obrebie_tego_wywolania[element_do_cofniecia];
						}
					}
					pozycje_zmienionych_elementow.clear(); // czyszcze wektor zmienionych elementow
														   // std::cout << "________________\n";
				}
				else if (czy_wszystko_sie_zgadzalo == true)
				{
					uzyte_w_obrebie_tego_wywolania[i] = 1;
					pozycje_zmienionych_elementow.push_back(i);
					// std::cout << "Pasuje wchodze glebiej w rekurencje :)\n\n";
					// std::cout << "Rekurencji przekazuje: \n";
					// wyswietl_statusy_elementow(pociete_fragmenty, uzyte_w_obrebie_tego_wywolania);
					// std::cout << "________________\n";
					szukaj_rozwiazania(wskaznik_na_rozwiazanie, max_ilosc_ciec, czas_start, uzyte_w_obrebie_tego_wywolania, pociete_fragmenty, czy_znalzalam); // pasuje kontynuuje
																																							   // std::cout << "Wyszlam z rekurencji. Statusy w tym poziomie: \n";
																																							   // wyswietl_statusy_elementow(pociete_fragmenty, uzyte_w_obrebie_tego_wywolania);
																																							   // std::cout << "\n";
				}
			}
			if (!pozycje_zmienionych_elementow.empty()) // jesli zdazylam cokolwiek zmienic w wektorze uzyc
			{
				// std::cout << "cofam pozycje zmienione" << '\n';
				for (int k = 0; k < pozycje_zmienionych_elementow.size(); k++)
				{
					int element_do_cofniecia = pozycje_zmienionych_elementow[k];
					uzyte_w_obrebie_tego_wywolania[element_do_cofniecia] = 0; // cofam na nieuzyte
																			  // std::cout << pociete_fragmenty[element_do_cofniecia] << "status: " << uzyte_w_obrebie_tego_wywolania[element_do_cofniecia];
				}
			}
			pozycje_zmienionych_elementow.clear(); // czyszcze wektor zmienionych elementow
		}
		// std::cout << "Tutaj zadna opcja nie pasowala\n";
		// std::cout << "Statusy tutaj: \n";
		// wyswietl_statusy_elementow(pociete_fragmenty,uzyte_w_obrebie_tego_wywolania);
		// std::cout << "\ncofam sie do poprzedniego\n";
		// jesli dotre do tego miejsca to oznacza ze sprawdzilam juz wszystko w obrebie tego wywolania funkcji rekurencyjnie
		//  jesli sprawdzilam wszystko i skonstruowalam w ten sposob rozwiazanie to super

		if (wskaznik_na_rozwiazanie->size() != max_ilosc_ciec) // jesli nie to

		{
			wskaznik_na_rozwiazanie->pop_back(); // musze pozbyc sie ostatniego elementu
		}
		if (!wskaznik_na_rozwiazanie->empty())
		{
			// std::cout << "Rozwiazanie: ";
			// wyswietl_mape(wskaznik_na_rozwiazanie);
			// std::cout << "\n";
		}

		// petla dobiega konca a tym samym konczy sie jedna rekurencja
	}
}
struct recursive_directory_range
{
	typedef boost::filesystem::recursive_directory_iterator iterator;
	recursive_directory_range(boost::filesystem::path p) : p_(p) {}

	iterator begin() { return boost::filesystem::recursive_directory_iterator(p_); }
	iterator end() { return boost::filesystem::recursive_directory_iterator(); }

	boost::filesystem::path p_;
};

bool replace(std::string &str, const std::string &from, const std::string &to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
int main()
{
	for (auto it : recursive_directory_range("./Mapowanie_instancje"))
	{
		std::string nazwa_pliku = it.path().c_str();
		std::cout << nazwa_pliku << std::endl;
		std::fstream plik;
		// std::cout << "Podaj nazwe pliku\n";
		// std::string nazwa_pliku;
		// std::cin >> nazwa_pliku;
		// plik.open(nazwa_pliku, std::ifstream::in);
		plik.open(nazwa_pliku, std::ifstream::in);

		std::map<int, int> mapa_rozmiarow{{15, 5}, {21, 6}, {28, 7}, {36, 8}, {45, 9}, {55, 10}, {66, 11}, {78, 12}, {91, 13}, {105, 14}, {120, 15}, {136, 16}};
		std::vector<int> pociete_fragmenty;
		std::string linia;
		std::string fragment;

		if (plik.is_open())
		{
			while (!plik.eof())
			{
				getline(plik, linia);
				std::stringstream stream_linii(linia);
				while (!stream_linii.eof())
				{
					getline(stream_linii, fragment, ' ');
					int dlugosc_fragmentu = stoi(fragment);
					pociete_fragmenty.push_back(dlugosc_fragmentu); // w wektorze mam wszystkie fragmenty
				}
			}
		}

		if (Czy_mozna_stworzyc_mape(pociete_fragmenty.size(), mapa_rozmiarow) == false) // sprawdzam czy ilosc elementow jest odpowiednia i zwracam komunikat jesli nie. Ilosc elementow obrazuje rozmiar wektora do ktorego wczytywalam elementy po kolei
		{
			std::cout << "Ilosc elementow nie jest odpowiednia aby stworzyc mape z takiego zbioru\n";
			return -1;
		}

		int spodziewana_liczb_ciec = mapa_rozmiarow[pociete_fragmenty.size()];
		std::cout << "Spodziewana liczba ciec: " << spodziewana_liczb_ciec << "\n";
		// std::sort(pociete_fragmenty.begin(), pociete_fragmenty.end());

		std::vector<int> Rozwiazanie;
		std::vector<int> *wskaznik_na_rozwiazanie = &Rozwiazanie;
		std::vector<int> uzyte = pociete_fragmenty;
		std::vector<int> *wskaznik_na_uzyte = &uzyte;
		uzyte = zeruj_wektor_uzyc(uzyte);

		/*int licznik = 0;
		for (auto element : pociete_fragmenty)
		{
			std::cout << licznik << " " << element << "\n";
			licznik++;
		}*/

		int max = najwiekszy_element(pociete_fragmenty);
		std::cout << "max: " << max << "\n";
		// int pozycja_max = szukaj_elementu(pociete_fragmenty, max);
		// uzyte[pozycja_max] = 1;     //oznaczam max jako uzyty

		int drugi_max = drugi_najwiekszy_element(pociete_fragmenty, max);
		std::cout << "drugi max: " << drugi_max << "\n";
		// int pozycja_drugi_max = szukaj_elementu(pociete_fragmenty, drugi_max);
		// uzyte[pozycja_drugi_max] = 1;   //oznaczam drugi max jako uzyty

		int roznica = max - drugi_max;
		std::cout << "roznica: " << roznica << "\n";
		int pozycja_roznicy = szukaj_elementu(pociete_fragmenty, roznica);
		std::cout << "pozycja roznicy: " << pozycja_roznicy << "\n";

		if (pozycja_roznicy != -1)
		{
			std::cout << "Dodaje do rozwiazania: " << pociete_fragmenty[pozycja_roznicy] << "\n";
			Rozwiazanie.push_back(pociete_fragmenty[pozycja_roznicy]); // dodaje ten pierwszy element do rozwiazania
			uzyte[pozycja_roznicy] = 1;								   // wynik odejmowania max-drugi_max tez jest uzyty
		}
		else
		{
			std::cout << "Dane niepoprawne, nie ma fragmentu o dlugosci max-drugi_max koncze program\n";
			return -1;
		}

		auto start = clock();

		bool rozwiazanie = false;
		bool *czy_znalazlam = &rozwiazanie;
		szukaj_rozwiazania(wskaznik_na_rozwiazanie, spodziewana_liczb_ciec, start, uzyte, pociete_fragmenty, czy_znalazlam);
		std::cout << "\n\n\n";
		double czas = policz_czas(start);

		if (rozwiazanie == false)
		{
			std::cout << "Brak rozwiazania dla takich danych\n";
			replace(nazwa_pliku, ".txt", "_wynik.txt");
			replace(nazwa_pliku, "Mapowanie_instancje", "Mapowanie_wyniki");
			std::ofstream out(nazwa_pliku);
			out << "Przekroczono czas szukania rozwiązania." << std::endl;
			out.close();
		}
		if (rozwiazanie == true)
		{
			std::cout << "ZNALEZIONO ROZWIAZANIE";
			wyswietl_mape(wskaznik_na_rozwiazanie);
			replace(nazwa_pliku, ".txt", "_wynik.txt");
			replace(nazwa_pliku, "Mapowanie_instancje", "Mapowanie_wyniki");
			std::ofstream out(nazwa_pliku);
			for (auto element : *wskaznik_na_rozwiazanie)
			{
				out << element << " ";
			}
			out << std::endl;
			out << "Czas: " << czas << "s" << std::endl;
			out.close();
		}
	}
}