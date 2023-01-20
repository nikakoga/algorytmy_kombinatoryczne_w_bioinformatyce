#include <fstream>
#include <iostream>
# include <map>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>


bool Czy_mozna_stworzyc_mape(int liczba_elementow, std::map<int,int> mapa)
{
    if (mapa.find(liczba_elementow) != mapa.end())//jesli istnieje taka wartosc w mapie
    {
        return true;
    }
    return false;
}


int main()
{
    std::fstream plik;
    std::cout << "Podaj nazwe pliku\n";
    std::string nazwa_pliku;
    std::cin >> nazwa_pliku;
    plik.open(nazwa_pliku, std::ifstream::in);

    std::map<int, int>mapa_rozmiarow{ {15,5},{21,6},{28,7},{36,8},{45,9},{55,10},{66,11},{78,12},{91,13},{105,14},{120,15},{136,16} };
    std::vector<int>pociete_fragmenty;
    std::string linia;
    std::string fragment;
    
    while (!plik.eof())
    {
        getline(plik, linia);
        std::stringstream stream_linii(linia);
        while (!stream_linii.eof())
        {
            getline(stream_linii, fragment, ' ');
            int dlugosc_fragmentu = stoi(fragment);
            pociete_fragmenty.push_back(dlugosc_fragmentu); //w wektorze mam wszystkie fragmenty
        }
    }
    
    if (Czy_mozna_stworzyc_mape(pociete_fragmenty.size(), mapa_rozmiarow) == false) //sprawdzam czy ilosc elementow jest odpowiednia i zwracam komunikat jesli nie. Ilosc elementow obrazuje rozmiar wektora do ktorego wczytywalam elementy po kolei
    {
        std::cout << "Ilosc elementow nie jest odpowiednia aby stworzyc mape z takiego zbioru\n";
        return;
    }

    int spodziewana_liczb_ciec = mapa_rozmiarow[pociete_fragmenty.size()];
    auto clock_start = std::chrono::high_resolution_clock::now();
    auto clock_end = std::chrono::high_resolution_clock::now();

    auto elapsed = 
    




}


