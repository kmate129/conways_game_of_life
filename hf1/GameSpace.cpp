#include "GameSpace.h"
#include <iostream>
#include <random>

GameSpace::GameSpace(const int width) : nRow(width), nColumn(width)
{
	table = std::vector<std::vector<int>>(width, std::vector<int>(width));
	std::random_device rD;
	std::default_random_engine rE(rD());
	std::uniform_int_distribution<int> dist(0, 100);

	for(auto& row : table)
	{
		for (auto& cell : row)
		{
			if (dist(rE) <= 10) 
			{
				cell = 1;
				nCells++;
			}
			else
			{
				cell = 0;
			}
		}
	}
}

GameSpace::GameSpace(const int height, const int width) : nRow(height), nColumn(width)
{
	table = std::vector<std::vector<int>>(height, std::vector<int>(width));
	std::random_device rD;
	std::default_random_engine rE(rD());
	std::uniform_int_distribution<int> dist(0, 100);

	for (auto& row : table)
	{
		for (auto& cell : row)
		{
			if (dist(rE) <= 10)
			{
				cell = 1;
				nCells++;
			}
			else
			{
				cell = 0;
			}
		}
	}
}

GameSpace::GameSpace(const int width, const double chance) : nRow(width), nColumn(width)
{
	table = std::vector<std::vector<int>>(width, std::vector<int>(width));
	std::random_device rD;
	std::default_random_engine rE(rD());
	std::uniform_int_distribution<int> dist(0, 1000);

	for (auto& row : table)
	{
		for (auto& cell : row)
		{
			if (static_cast<double>(dist(rE)) / 1000 <= chance)
			{
				cell = 1;
				nCells++;
			}
			else
			{
				cell = 0;
			}
		}
	}
}

GameSpace::GameSpace(const int height, const int width, const double chance) : nRow(height), nColumn(width)
{
	table = std::vector<std::vector<int>>(height, std::vector<int>(width));
	std::random_device rD;
	std::default_random_engine rE(rD());
	std::uniform_int_distribution<int> dist(0, 1000);

	for (auto& row : table)
	{
		for (auto& cell : row)
		{
			if (static_cast<double>(dist(rE)) / 1000 <= chance)
			{
				cell = 1;
				nCells++;
			}
			else
			{
				cell = 0;
			}
		}
	}
}

GameSpace::GameSpace(const int height, const int width, const int top, const int left, const std::vector<std::vector<int>>& vector) : nRow(height), nColumn(width)
{
	table = std::vector<std::vector<int>>(height, std::vector<int>(width));

	int i = top;
	size_t k = 0;
	std::vector<std::vector<int>>::size_type vectorHeight = vector.size();
	std::vector<int>::size_type vectorWidth = vector[0].size();

	while (i<height && k<vectorHeight)
	{
		int j = left;
		size_t l = 0;
		while (j < width && l<vectorWidth )
		{
			table[i][j] = vector[k][l];
			if (table[i][j] == 1) 
			{
				nCells++;
			}

			j++;
			l++;
		}

		i++;
		k++;
	}
}

std::ostream& operator<<(std::ostream& os, const GameSpace& rhs)
{
	std::string toReturn = "";

	for (const auto& row : rhs.GetTable())
	{
		for (const auto& cell : row)
		{
			if (cell == 0)
			{
				toReturn += "O ";
			}
			else
			{
				toReturn += "X ";
			}
		}

		toReturn += "\n";
	}

	os << toReturn;
	return os;
}

std::vector<std::vector<int>> GameSpace::GetTable() const
{
	return table;
}

void GameSpace::NextRound()
{
	nCells = 0;
	std::vector<std::vector<int>> temp(nRow, std::vector<int>(nColumn));

	for (int i = 0; i < nRow; ++i)
	{
		for (int j = 0; j < nColumn; ++j)
		{
			temp[i][j] = Calculate(i, j);
		}
	}

	for (int i = 0; i < nRow; ++i)
	{
		for (int j = 0; j < nColumn; ++j)
		{
			if (temp[i][j] == 2 || temp[i][j] == 3)
			{
				table[i][j] = 1;
				nCells++;
			}
			if (temp[i][j] == 4 || temp[i][j] == 5)
			{
				table[i][j] = 0;
			}
		}
	}

	nRound++;
}

// 2: marad az 1es, 3: feléled,  4: meghal 5: marad a 0as
int GameSpace::Calculate(int i, int j) const
{
	int count = 0;
	int cell = table[i][j];

	int startRow = i - 1;
	int startColumn = j - 1;
	int endRow = i + 1;
	int endColumn = j + 1;

	if (i == 0)
	{
		startRow = i;
	}
	if (i == nRow - 1)
	{
		endRow = i;
	}
	if (j == 0)
	{
		startColumn = j;
	}
	if (j == nColumn - 1)
	{
		endColumn = j;
	}
	
	for (int k=startRow; k <= endRow; ++k)
	{
		for (int l=startColumn; l <= endColumn; ++l)
		{
			if ((k != i || l != j) && table[k][l] == 1)
			{
				count++;
			}
		}
	}

	if (cell == 1 && (count == 2 || count == 3))
	{
		return 2;
	}
	else if (cell == 1 && (count < 2 || count >3))
	{
		return 4;
	}
	else if (cell == 0 && count == 3)
	{
		return 3;
	}
	else
	{
		return 5;
	}
}