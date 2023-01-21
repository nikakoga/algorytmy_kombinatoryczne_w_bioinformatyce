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

void wyswietl_mape(std::vector<int> rozwiazanie)
{
    for (auto element : rozwiazanie)
    {
        std::cout << element << " ";
    }
}

int szukaj_elementu_jesli_jest_niewykorzystany(int wartosc, std::vector<int>uzyte, std::vector<int>pociete_fragmenty)
{
    for (int i = 0; i < pociete_fragmenty.size(); i++)
    {
        if (pociete_fragmenty[i] == wartosc)
        {
            if (uzyte[i] == 0)//sprawdzam czy ten element nie jest wykorzystany
            {
                return i;
            }
        }
    }

    return -1; //zwracam -1 jesli nie ma nieuzytego elementu o takiej wartosci 
}

bool Czy_dotychczasowe_rozwiazanie_sie_zgadza(std::vector<int> rozwiazanie, std::vector<int>uzyte, std::vector<int>pociete_fragmenty)
{
    int suma = 0;
    for (int i = rozwiazanie.size()-1; i > 0; i--)//-1 tam jest ostatni element bo numeruje wektor od 0
    {
        suma += rozwiazanie[i];
        if (i < rozwiazanie.size())// dlatego ze nie sprawdzam czy wlasnie dodany do rozwiazania element jest oznaczony jako uzyty, bo jest na pewno.
        {
            int nr_elementu = szukaj_elementu_jesli_jest_niewykorzystany(suma, uzyte, pociete_fragmenty);
            if (nr_elementu != -1)
            {
                uzyte[nr_elementu] = 1;
            }
            if (nr_elementu == -1)
            {
                return false;
            }
        }
    }
    return true;
}

void szukaj_rozwiazania(std::vector<int> rozwiazanie, int max_ilosc_ciec, clock_t czas_start, std::vector<int> uzyte_w_obrebie_tego_wywolania, std::vector<int>pociete_fragmenty)
{
    if (rozwiazanie.size() == max_ilosc_ciec)
    {
        std::cout << "Znaleziono mape: ";
        wyswietl_mape(rozwiazanie);
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
        for (int i = 0; i < uzyte_w_obrebie_tego_wywolania.size(); i++) //iteruje po tablicy uzyc fragmentow
        {
            if (uzyte_w_obrebie_tego_wywolania[i] == 0)//jesli jeszcze nie uzylam tego fragmentu
            {
                rozwiazanie.push_back(pociete_fragmenty[i]);//dodaje go na probe do rozwiazania
                int suma = 0;
                bool czy_wszystko_sie_zgadzalo = true;
                std::vector<int>pozycje_zmienionych_elementow;

                for (int i = rozwiazanie.size() - 1; i > 0; i--)//-1 tam jest ostatni element bo numeruje wektor od 0
                {
                    suma += rozwiazanie[i];
                    if (i < rozwiazanie.size())// dlatego ze nie sprawdzam czy wlasnie dodany do rozwiazania element jest oznaczony jako uzyty, bo jest na pewno.
                    {
                        int nr_elementu = szukaj_elementu_jesli_jest_niewykorzystany(suma, uzyte_w_obrebie_tego_wywolania, pociete_fragmenty);
                        if (nr_elementu != -1) //gdy funkcja nie zwraca -1 to znalazla element o zadanej wartosci ktory jest nieuzyty
                        {
                            uzyte_w_obrebie_tego_wywolania[nr_elementu] = 1; //jesli nie jest wykorzystany ustawiam ze teraz juz jest
                            pozycje_zmienionych_elementow.push_back(nr_elementu);
                        }
                        if (nr_elementu == -1)//znaleziony element jest juz wykorzystany
                        {
                            czy_wszystko_sie_zgadzalo = false;
                            break;
                        }
                    }
                }
                if (czy_wszystko_sie_zgadzalo == false)
                {
                    rozwiazanie.pop_back();//nie pasuje, usuwam to co dodalam
                    
                    if (!pozycje_zmienionych_elementow.empty()) //jesli zdazylam cokolwiek zmienic w wektorze uzyc
                    {
                        for (int i = 0; i < pozycje_zmienionych_elementow.size(); i++)
                        {
                            int element_do_cofniecia = pozycje_zmienionych_elementow[i];
                            uzyte_w_obrebie_tego_wywolania[element_do_cofniecia] = 0;//cofam na nieuzyte
                        }
                    }
                    pozycje_zmienionych_elementow.clear(); //czyszcze wektor zmienionych elementow
                }
                else
                {
                    szukaj_rozwiazania(rozwiazanie, max_ilosc_ciec, czas_start, uzyte_w_obrebie_tego_wywolania, pociete_fragmenty);//pasuje kontynuuje
                }   
            }
            //jesli dotre do tego miejsca to oznacza ze sprawdzilam juz wszystko w obrebie tego wywolania funkcji rekurencyjnie
            rozwiazanie.pop_back(); //musze pozbyc sie ostatniego elementu !!!!!!!!!!!!!!!!! TO NIC NIE DA, OPERUJESZ NA KOPII
            //petla dobiega konca a tym samym konczy sie jedna rekurencja
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
 
    szukaj_rozwiazania(Rozwiazanie,spodziewana_liczb_ciec,start,uzyte,pociete_fragmenty);
    

        
    




}


