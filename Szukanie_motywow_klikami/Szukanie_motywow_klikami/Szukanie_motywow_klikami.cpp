#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "Sekwencja.h"
#include "Pomocniecze.h"

#define ILOSC_PLIKOW 1
#define ILOSC_SEKWENCJI_W_PLIKU 5


int main()
{
        
    std::cout << "Podaj prog wiarygodnosci\n";
    unsigned int prog_wiarygodnosci = 30;
    //std::cin >> prog_wiarygodnosci;

    std::cout << "Podaj dlugosc podciagow\n";
    unsigned int dlugosc_podciagu = 4;
    //std::cin >> dlugosc_podciagu;

    std::vector<std::string> Nazwy_plikow = { "plik_1.fasta", "plik_1.qual" };
    std::fstream f_sekwencja, f_wiarygodnosc;

    Graf graf(1);

    for (int i = 0; i < ILOSC_PLIKOW * 2; i+=2)
    {
        std::string s = Nazwy_plikow[i];
        std::string w = Nazwy_plikow[i+1];
        f_sekwencja.open(s, std::ifstream::in);
        f_wiarygodnosc.open(w, std::ifstream::in);

        std::vector<std::string> wektor_sekwencji = tworzenie_wektora_z_elementami_pliku(f_sekwencja);
        std::vector<std::string> wektor_wiarygodnosci = tworzenie_wektora_z_elementami_pliku(f_wiarygodnosc);
        std::string pojedyncza_sekwencja_z_pliku;
        std::string pojedyncza_wiarygodnosc_sekwencji_z_pliku;

        for (int i = 0; i < ILOSC_SEKWENCJI_W_PLIKU; i++) //dodawanie sekwencji z jednego pliku do mapy sekwencji
        {
            pojedyncza_sekwencja_z_pliku = wektor_sekwencji[i];
            pojedyncza_wiarygodnosc_sekwencji_z_pliku = wektor_wiarygodnosci[i];
            Sekwencja aktualna_sekwencja(i + 1, pojedyncza_sekwencja_z_pliku, dlugosc_podciagu); // i+1 bo numeruje sekwencje od 1
            aktualna_sekwencja.uwzglednianie_progu_wiarygodnosci(pojedyncza_wiarygodnosc_sekwencji_z_pliku, prog_wiarygodnosci);
            auto wierzcholki_do_dodania = aktualna_sekwencja.tworzenie_podciagow();
            graf.dodawanie_wierzcholkow_do_grafu(wierzcholki_do_dodania);
            
            
        }
 
        f_sekwencja.close();
        f_wiarygodnosc.close();
    }


  
           
        
        
    


}

