#pragma once
#include <string>
class Nukleotyd
{
	int pozycja_w_wiarygodnej;
	int pozycja_w_oryginale;
	std::string podciag;

public:
	Nukleotyd(int pozycja_w_wiar, int pozycja_w_oryg,std::string podci)
	{
		pozycja_w_oryginale = pozycja_w_oryg;
		pozycja_w_wiarygodnej = pozycja_w_wiar;
		podciag = podci;
	}
};

