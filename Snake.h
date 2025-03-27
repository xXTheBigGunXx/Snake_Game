#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <utility>

class Snake {
private:
	std::list < std::pair<int, int>> _snakes_body;
	const int _snakes_squere_witdh = 60;

	int _x_start;
	int _y_start;

	int _x_offset;
	int _y_offset;

	std::pair<int, int> _accseleration;
public:
	Snake(int x_offset, int y_offset, int squares_length);
	void DistributeAccseleration();
	std::list<std::pair<int, int>>::iterator Begin();
	std::list<std::pair<int, int>>::iterator End();
	int GetSquaresLength();
};

#endif
