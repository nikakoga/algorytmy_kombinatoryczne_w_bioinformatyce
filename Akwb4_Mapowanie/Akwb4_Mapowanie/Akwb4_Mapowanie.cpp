#include <fstream>
#include <iostream>
# include <map>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>


bool Czy_mozna_stworzyc_mape(int liczba_elementow, std::map<int,int> mapa)
{
    if (mapa.find(liczba_elementow) != mapa.end())//jesli istnieje taka wartosc w mapie
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
        if (fragmenty[i] > drugi_max && fragmenty[i]<max)
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
    return-1;
}

int Znajdz_max_minus_prawie_max_w_wektorze(std::vector<int> fragmenty, int max, int prawie_max)//jesli nie ma wyniku roznicy max-prawie max to dane sa zle
{
    int roznica_max_prawie_max = max - prawie_max;
   int znalezione= szukaj_elementu(fragmenty, roznica_max_prawie_max);
   return znalezione;

}

std::vector<int> zeruj_wektor_uzyc(std::vector<int>uzyte)
{

    for (int i = 0; i < uzyte.size(); i++)
    {
        uzyte[i] = 0;
    }
    return uzyte;
}

double policz_czas (clock_t start)
{
    auto stop = clock();
    double czas_wykonywania_w_sekundach = (double)(stop - start) / (double)CLOCKS_PER_SEC;

    return czas_wykonywania_w_sekundach;

}

void wyswietl_mape(std::vector<int>* wskaznik_rozwiazanie)
{
    for (auto element : *wskaznik_rozwiazanie)
    {
        std::cout << element << " ";
    }
}

bool Czy_dotychczasowe_rozwiazanie_sie_zgadza(int dodawana_dlugosc)
{
    //sprawdzasz czy sie sumy zgadzaja
}

void szukaj_rozwiazania(std::vector<int>* wskaznik_rozwiazanie, int max_ilosc_ciec, clock_t czas_start, std::vector<int>* wskaznik_na_uzyte, std::vector<int>pociete_fragmenty)
{
    if (wskaznik_rozwiazanie->size() == max_ilosc_ciec)
    {
        std::cout << "Znaleziono mape: ";
        wyswietl_mape(wskaznik_rozwiazanie);
        std::cout << "Czas szukania rozwiazania: " << policz_czas(czas_start) << "\n";
        return;
    }
    if (policz_czas(czas_start) >=3600)
    {
        std::cout << "Przekroczono czas dla szukania rozwiaznania\nKoncze program";
        return;
    }
    else
    {

        for (int i = 0; i < wskaznik_na_uzyte->size(); i++) //iteruje po tablicy uzyc fragmentow
        {
            if (&wskaznik_na_uzyte[i] == 0)//jesli jeszcze nie uzylam tego fragmentu
            {
                wskaznik_rozwiazanie->push_back(pociete_fragmenty[i]);//dodaje go na probe do rozwiazania
                if (Czy_dotychczasowe_rozwiazanie_sie_zgadza(pociete_fragmenty[i]) == true)//sprawdzam czy pasuje
                {
                    szukaj_rozwiazania(wskaznik_rozwiazanie, max_ilosc_ciec, czas_start, wskaznik_na_uzyte, pociete_fragmenty);//pasuje kontynuuje
                }
                else
                {
                    wskaznik_rozwiazanie->pop_back();//nie pasuje, usuwam to co dodalam
                    //probuje z nastepnym niewykorzystanym w nowym obiegu petli
                }
            }
            
        }
        
        

    }


    
   
    
}

int main()
{
    std::fstream plik;
   // std::cout << "Podaj nazwe pliku\n";
    //std::string nazwa_pliku;
   // std::cin >> nazwa_pliku;
   // plik.open(nazwa_pliku, std::ifstream::in);
    plik.open("instancja1.txt", std::ifstream::in);

    std::map<int, int>mapa_rozmiarow{ {15,5},{21,6},{28,7},{36,8},{45,9},{55,10},{66,11},{78,12},{91,13},{105,14},{120,15},{136,16} };
    std::vector<int>pociete_fragmenty;
    std::string linia;
    std::string fragment;
    
    if (plik.is_open())
    {
        while (!plik.eof())
        {
            getline(plik,linia);
            std::stringstream stream_linii(linia);
            while (!stream_linii.eof())
            {
                getline(stream_linii, fragment, ' ');
                int dlugosc_fragmentu = stoi(fragment);
                pociete_fragmenty.push_back(dlugosc_fragmentu); //w wektorze mam wszystkie fragmenty
            }
        }
    }
    
    
    if (Czy_mozna_stworzyc_mape(pociete_fragmenty.size(), mapa_rozmiarow) == false) //sprawdzam czy ilosc elementow jest odpowiednia i zwracam komunikat jesli nie. Ilosc elementow obrazuje rozmiar wektora do ktorego wczytywalam elementy po kolei
    {
        std::cout << "Ilosc elementow nie jest odpowiednia aby stworzyc mape z takiego zbioru\n";
        return -1;
    }

    int spodziewana_liczb_ciec = mapa_rozmiarow[pociete_fragmenty.size()];

    std::vector<int> Rozwiazanie;
    std::vector<int>* wskaznik_na_rozwiazanie = &Rozwiazanie;
    std::vector<int> uzyte = pociete_fragmenty;
    std::vector<int>* wskaznik_na_uzyte = &uzyte;
    uzyte=zeruj_wektor_uzyc(uzyte);
    

    int max = najwiekszy_element(pociete_fragmenty);
    int pozycja_max = szukaj_elementu(pociete_fragmenty, max);
    uzyte[pozycja_max] = 1;     //oznaczam max jako uzyty
    
    int drugi_max = drugi_najwiekszy_element(pociete_fragmenty, max);
    int pozycja_drugi_max = szukaj_elementu(pociete_fragmenty, drugi_max);
    uzyte[pozycja_drugi_max] = 1;   //oznaczam drugi max jako uzyty
   
    if (int pozycja_w_wektorze = Znajdz_max_minus_prawie_max_w_wektorze(pociete_fragmenty, max, drugi_max) !=-1) 
    {
        Rozwiazanie.push_back(pociete_fragmenty[pozycja_w_wektorze]); //dodaje ten pierwszy element do rozwiazania
        uzyte[pozycja_w_wektorze] = 1; //wynik odejmowania max-drugi_max tez jest uzyty
    }
    else
    {
        std::cout << "Dane niepoprawne, nie ma fragmentu o dlugosci max-drugi_max koncze program\n";
        return -1;
    }

    auto start = clock();
 
    szukaj_rozwiazania(wskaznik_na_rozwiazanie,spodziewana_liczb_ciec,start,wskaznik_na_uzyte,pociete_fragmenty);
    

        
    




}


