#pragma once

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
            sekwencja += line + "\n";
        }

        else
        {
            getline(file, line);
            if (line[0] != '>') //jesli wlasnie nie zaczela sie nowa sekwencja
            {
                sekwencja += line + "\n"; //dodaje to co zczytalam 
            }
            else if (line[0] == '>') //jesli wlasnie zaczela sie nowa sekwencja
            {
                Wszystkie_sekwencje_z_pliku.push_back(sekwencja); //dodaje to co mam dotychczas
                sekwencja = line + "\n"; //zaczynam tworzyc nowa sekwencje, ktora zaczyna sie od zczytanego wlasnie ">"
            }
        }

    }
    Wszystkie_sekwencje_z_pliku.push_back(sekwencja); //aby ostatnia sekwencja dodala sie do wektora bo po ostatniej sekwencji nie ma ju¿ ">" które dodaje poprzedni¹
    return Wszystkie_sekwencje_z_pliku;
}

