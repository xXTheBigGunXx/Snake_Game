#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <utility>

class Snake {
public:
	std::list < std::pair<int, int>> _snakes_body;
	const int _snakes_squere_width = 60;
	int _move_per_frame;

	int _x_start;
	int _y_start;

	int _x_offset;
	int _y_offset;
	const int _speed = 8;

	std::pair<int, int> _accseleration;
	std::pair<int, int> _temp_accseleration;

	Snake(int x_offset, int y_offset, int squares_length, int _FPS);
	std::pair<int, int> DistributeAccseleration();
	std::list<std::pair<int, int>>::iterator Begin();
	std::list<std::pair<int, int>>::iterator End();
	int GetSquaresLength();
	void Push_Front(const std::pair<int, int>& pair);
	void Pop_Back();
	std::pair<int, int> IncramentedPair();
	bool AccselerationZero();
};

#endif
