#include "Snake.h"
#include "TaskUtils.h"

Snake::Snake(int x_offset, int y_offset, int squares_length) {
	_x_start = 0;
	_y_start = 0;

	_x_offset = x_offset;
	_y_offset = y_offset;

	_accseleration = std::make_pair(0, 0);

	_snakes_body.push_back(std::make_pair(_x_offset + squares_length/2, _y_offset + squares_length/2));
	_snakes_body.push_back(std::make_pair(_x_offset + squares_length/2 - _snakes_squere_witdh, _y_offset + squares_length/2));
}

void Snake::DistributeAccseleration() {
	switch (TaskUtils::KeyPressed()) {
		case 'w': _accseleration = std::make_pair(0,-1);
		case 's': _accseleration = std::make_pair(0, 1);
		case 'a': _accseleration = std::make_pair(-1, 0);
		case 'd': _accseleration = std::make_pair(1, 0);
	}
}

std::list<std::pair<int, int>>::iterator Snake::Begin() { return _snakes_body.begin(); }
std::list<std::pair<int, int>>::iterator Snake::End() { return _snakes_body.end(); }
int Snake::GetSquaresLength() { return _snakes_squere_witdh; }