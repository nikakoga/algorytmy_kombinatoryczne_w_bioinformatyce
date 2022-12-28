#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Sekwencja.h"

#define ILOSC_PLIKOW 5
#define ILOSC_SEKWENCJI_W_PLIKU 5

// TO DO moze przeklej to potem do jakiegos pliku osobno, zeby tu byl tylko main
std::vector<std::string> tworzenie_wektora_z_elementami_pliku(std::fstream& file)
{
    std::vector<std::string> Wszystkie_sekwencje_z_pliku;
    
    std::string sekwencja = "";
    std::string line;

    while (!file.eof())
    {

        if (sekwencja.empty()) //jesli sekwencja jest pusta to wczytuje pierwsza linie, ktora zawiera ">" na poczatku. Wazne tylko przy pierwszym czytaniu z pliku
        {
            getline(file, line);
            sekwencja += line;
        }
        
        else 
        {
            getline(file, line);
            if (line[0] != '>') //jesli wlasnie nie zaczela sie nowa sekwencja
            {
                sekwencja += line; //dodaje to co zczytalam 
            }
            else if (line[0] == '>') //jesli wlasnie zaczela sie nowa sekwencja
            {
                Wszystkie_sekwencje_z_pliku.push_back(sekwencja); //dodaje to co mam dotychczas
                sekwencja = line; //zaczynam tworzyc nowa sekwencje, ktora zaczyna sie od zczytanego wlasnie ">"
            }
        }

    }
    
    return Wszystkie_sekwencje_z_pliku;
}

int main()
{
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

        for (int i = 0; i < ILOSC_SEKWENCJI_W_PLIKU; i++)
        {
            pojedyncza_sekwencja_z_pliku = wektor_sekwencji[i];
            pojedyncza_wiarygodnosc_z_pliku = wektor_wiarygodnosci[i];
            Sekwencja Aktualna_sekwencja (i,pojedyncza_sekwencja_z_pliku); //PAMIETAJ ZE SEKWENCJE NUMERUJESZ OD 0 A NUKLEOTYDY OD 1
            Aktualna_sekwencja.uwzglednianie_progu_wiarygodnosci(pojedyncza_wiarygodnosc_z_pliku, prog_wiarygodnosci);
        }
        
        //TO DO jakis container na te sekwencje zeby moc sie do nich dostawac
 
        f_sekwencja.close();
        f_wiarygodnosc.close();
    }


  
           
        
        
    


}

