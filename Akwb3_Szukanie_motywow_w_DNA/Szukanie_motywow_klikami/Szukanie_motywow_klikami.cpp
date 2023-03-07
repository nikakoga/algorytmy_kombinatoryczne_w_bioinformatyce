#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "Sekwencja.h"
#include "Pomocniecze.h"

//ILOSC PLIKOW I ILOSC SEKWENCJI DEFINIUJE W PLIKU WIERZCHOLEK.H

int main()
{
    std::vector<std::string> Nazwy_plikow = { "Instancja_1.fasta", "Instancja_1.qual","Instancja_2.fasta", "Instancja_2.qual","Instancja_3.fasta", "Instancja_3.qual"};
    std::fstream f_sekwencja, f_wiarygodnosc;

    srand(time(0));
    int nr_pliku = 1;
    
    for (int i = 0; i < ILOSC_PLIKOW * 2; i+=2)
    {
        std::cout << "PLIK NR "<<nr_pliku<<"\n";
        int nr_testu = 1;

        for (int p = 0; p < ILE_POWTORZEN_DLA_PLIKU; p++)
        {
            std::cout << "Podaj prog wiarygodnosci\n";
            unsigned int prog_wiarygodnosci;
            std::cin >> prog_wiarygodnosci;

            std::cout << "Podaj dlugosc podciagow\n";
            unsigned int dlugosc_podciagu;
            std::cin >> dlugosc_podciagu;

            Graf graf(1);
            graf.set_dlugosc_podciagu(dlugosc_podciagu);

            std::string s = Nazwy_plikow[i];
            std::string w = Nazwy_plikow[i + 1];
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
                std::unordered_map<int, Wierzcholek*> wierzcholki_w_tej_sekwencji = aktualna_sekwencja.tworzenie_podciagow();

                graf.dodawanie_wierzcholkow_do_grafu(wierzcholki_w_tej_sekwencji);


            }

            f_sekwencja.close();
            f_wiarygodnosc.close();

            //graf.wyswietl_mape_podciagow();
            //graf.wyswietl_mape_dla_konkretnego_podciagu("GGGA");
            graf.ustalanie_sasiedztwa();
            graf.generuj_rozwiazanie();
            std::cout << "\nROZAWIAZANIE DLA PLIKU NR " << nr_pliku << "\n";
            std::cout << "TEST NR " << nr_testu << "\n";
            nr_testu++;
            graf.wyswietl_rozwiazanie();
            std::cout << "\n";
        }
       
        nr_pliku++;
      
    }

}

