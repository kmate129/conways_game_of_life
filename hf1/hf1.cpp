#include <iostream>
#include "GameSpace.h"

int main()
{
	std::vector<std::vector<int>> v(5);
	for (auto& e : v)
	{
		e = std::vector<int>(2);
		for (auto& f : e)
		{
			f = 1;
		}
	}

	GameSpace g(8, 8, 2, 2, v);
	std::cout << "Round: " << g.nRound << std::endl << g << std::endl;
	
	std::string a;

	while (g.nRound <= 100 && g.nCells != 0)
	{
		if (std::cin.get() == '\n')
		{
			g.NextRound();
			std::cout << "Round: " << g.nRound << std::endl << g << std::endl;
		}
	}
}

