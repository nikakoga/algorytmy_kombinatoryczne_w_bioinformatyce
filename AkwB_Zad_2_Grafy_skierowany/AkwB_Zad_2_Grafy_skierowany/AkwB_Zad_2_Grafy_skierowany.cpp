#include <fstream>
#include "Verticle.h"
#include "Graph.h"



int main()
{
    std::fstream file;
    std::cout << "Podaj nazwe_pliku wejsciowego\n";
    std::string filename = "Graf.txt";
    //std::cin >> filename;
    file.open(filename, std::ifstream::in);
    

    if (file.is_open())
    {
        
        try
        {
            if (file.peek() == std::fstream::traits_type::eof())
            {
                throw std::invalid_argument("ERROR, plik ktory chcesz uzyc jest pusty");
            }

            std::string text_from_file;
            Graph graph;

            while (!file.eof())
            {                
                getline(file, text_from_file);
                Verticle current_verticle(text_from_file);
                graph.add_verticle(current_verticle);         
            }

            //ODKOMENTUJ POTEM
            /*if (!graph.is_graph_adjoint())
            {
                throw std::invalid_argument("ERROR, Graf nie jest sprzezony");
            }*/
            
            //TUTAJ ZA CZASOW LISTY POPRZEDNIKOW
            //graph.generate_prev_neighbours_list_for_graph();
            //graph.fill_prev_neighbours_to_each_verticle_class();
            //graph.Show_prev_neighbours_list(); 

            graph.generate_prev_neighbours_map_for_graph();
            graph.Show_prev_neighbour_map();
            graph.Create_unordered_set_for_each_verticle();
            std::cout << "\n\n";
            graph.show_prev_neighbours_for_each_verticle();
            //std::cout << graph.generate_prev_neighbour_list_for_graph(); // NAPRAW BO NIE DZIALA :)
            std::cout << "Koniec\n";
            

            std::fstream new_file;
            std::cout << "Podaj nazwe_pliku wynikowego\n";
            std::string new_file_name;
            std::cin >> new_file_name;
            new_file.open(new_file_name, std::ifstream::out);
            

            if (new_file.is_open())
            {
                new_file << graph.generate_next_neighbour_list_for_graph();
            }            
            else 
            {
                throw std::invalid_argument("Nie udalo sie otworzyc pliku wynikowego aby zapisac");
            }

        }

        catch (std::invalid_argument& exception) //potem moze dorob takie bardziej sensowne lapanie niz wszystkiego zebys wiedziala co sie gdzie psuje a nie ze generalnie cos
        {
            std::cout << exception.what();
        }
        
    }

    else
    {
        std::cout << "Plik nie zostal otwarty\n";
    }

    file.close();

    
}


