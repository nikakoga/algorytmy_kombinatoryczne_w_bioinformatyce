#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "Sekwencja.h"
#include "Pomocniecze.h"

#define ILOSC_PLIKOW 5
#define ILOSC_SEKWENCJI_W_PLIKU 5

int main()
{
    std::unordered_map<int,Sekwencja *> Mapa_sekwencji;

    std::cout << "Podaj prog wiarygodnosci\n";
    unsigned int prog_wiarygodnosci = 0;
    std::cin >> prog_wiarygodnosci;

    std::cout << "Podaj dlugosc podciagow\n";
    unsigned int podciagi = 0;
    std::cin >> podciagi;

    std::vector<std::string> Nazwy_plikow = { "file_1_sekwencja.txt", "file_1_wiarygodnosc.txt", "file_2_sekwencja.txt", "file_2_wiarygodnosc.txt", "file_3_sekwencja.txt", "file_3_wiarygodnosc.txt", "file_4_sekwencja.txt", "file_4_wiarygodnosc.txt" };
    std::fstream f_sekwencja, f_wiarygodnosc;

    for (int i = 0; i < ILOSC_PLIKOW * 2; i+=2)
    {
        std::string s = Nazwy_plikow[i];
        std::string w = Nazwy_plikow[i+1];
        f_sekwencja.open(s, std::ifstream::in);
        f_wiarygodnosc.open(w, std::ifstream::in);

        std::vector<std::string> wektor_sekwencji = tworzenie_wektora_z_elementami_pliku(f_sekwencja);
        std::vector<std::string> wektor_wiarygodnosci = tworzenie_wektora_z_elementami_pliku(f_wiarygodnosc);
        std::string pojedyncza_sekwencja_z_pliku;
        std::string pojedyncza_wiarygodnosc_z_pliku;

        for (int i = 0; i < ILOSC_SEKWENCJI_W_PLIKU; i++) //dodawanie sekwencji z jednego pliku do mapy sekwencjigit
        {
            pojedyncza_sekwencja_z_pliku = wektor_sekwencji[i];
            pojedyncza_wiarygodnosc_z_pliku = wektor_wiarygodnosci[i];
            Sekwencja* Wskaznik_na_aktualna_sekwencje = new Sekwencja(i, pojedyncza_sekwencja_z_pliku);
            Mapa_sekwencji.insert({i+1,Wskaznik_na_aktualna_sekwencje}); //SEKWENCJE NUMERUJESZ OD 1
            Wskaznik_na_aktualna_sekwencje->uwzglednianie_progu_wiarygodnosci(pojedyncza_wiarygodnosc_z_pliku, prog_wiarygodnosci); //-> bo tak sie odwolujesz do metod i pol z wskaznika
        }
 
        f_sekwencja.close();
        f_wiarygodnosc.close();
    }


  
           
        
        
    


}

