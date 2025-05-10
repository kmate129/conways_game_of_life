#pragma once

#include <vector>
#include <string>

class GameSpace
{
public:
	GameSpace(const int width);
	GameSpace(const int height, const int width);
	GameSpace(const int width, const double chance);
	GameSpace(const int height, const int width, const double chance);
	GameSpace(const int height, const int width, const int top, const int left, const std::vector<std::vector<int>>& vector);

	int nRound = 1;
	int nCells;

	friend std::ostream& operator<<(std::ostream& os, const GameSpace& rhs);

	std::vector<std::vector<int>> GetTable() const;
	void NextRound();
private:
	std::vector<std::vector<int>> table;
	int nRow;
	int nColumn;

	int Calculate(int i, int j) const;
};
