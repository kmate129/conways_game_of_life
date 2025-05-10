#include <iostream>
#include "GameSpace.h"
#include <chrono> 

int main()
{
	auto start = std::chrono::high_resolution_clock::now();

	GameSpace g(1024, 1024, 0.3);

	while (g.nRound <= 1000 && g.nCells != 0)
	{
		g.NextRound();
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time elapsed: " << duration.count() << " ms" << std::endl;
}

