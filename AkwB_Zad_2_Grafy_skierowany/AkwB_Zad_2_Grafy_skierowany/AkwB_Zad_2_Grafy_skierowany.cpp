#include <fstream>
#include "Verticle.h"
#include "Graph.h"



int main()
{
	std::fstream file;
	std::cout << "Podaj nazwe_pliku wejsciowego\n";
	std::string filename;
	std::cin >> filename;
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


			graph.preparing_graph();

			if (!graph.is_graph_adjoint())
			{
				throw std::invalid_argument("Graf nie jest sprzezony bo zbior nastepnikow dla 2 wierzcholkow ma czesc wspolna inna niz wszystko i inna niz nic\n");
			}

			std::cout << "Graf sprzezony\n";
			graph.Get_czy_liniowy();
			graph.create_oryginal_graph();


			std::fstream new_file;
			std::cout << "\nPodaj nazwe_pliku wynikowego\n";
			std::string new_file_name;
			std::cin >> new_file_name;
			new_file.open(new_file_name, std::ifstream::out);


			if (new_file.is_open())
			{
				auto graf_sprzezony = graph.Get_adjoint_map();
				
				for (auto element : graf_sprzezony)
				{
					if (element.second != ">") //zeby nie zabierac tego z izolowanych wierzcholkow, one na koncu nie maja | ktore trzeba odjac
					{
						element.second.pop_back(); //gdyby nie to kazdy element mialby na koncu "|" a to niezgodne z formatem wejscia
					}
					
					new_file << element.first <<element.second <<"\n";
				}
					
					
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


