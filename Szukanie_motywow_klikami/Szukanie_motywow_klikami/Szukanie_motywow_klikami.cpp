#include <iostream>
#include <fstream>
#include <string>
#include "Sekwencja.h"

#define ILOSC_PLIKOW 5

int main()
{
    std::cout << "Podaj prog wiarygodnosci\n";
    unsigned int wiarygodnosc = 0;
    std::cin >> wiarygodnosc;

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

        Sekwencja Aktualna_sekwencja = (f_sekwencja);
        Aktualna_sekwencja.uwzglednianie_progu_wiarygodnosci(f_wiarygodnosc, wiarygodnosc);
 
        f_sekwencja.close();
        f_wiarygodnosc.close();
    }


  
           
        
        
    


}

