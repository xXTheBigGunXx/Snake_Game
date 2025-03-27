#include "Snake.h"
#include "TaskUtils.h"
#include <iostream>

Snake::Snake(int x_offset, int y_offset, int squares_length, int _FPS) {
	_move_per_frame = _FPS / _snakes_squere_width * _speed;
	_x_start = 0;
	_y_start = 0;

	_x_offset = x_offset;
	_y_offset = y_offset;

	_accseleration = std::make_pair(0, 0);
	_temp_accseleration = std::make_pair(0, 0);

	_snakes_body.push_back(std::make_pair(_x_offset + squares_length/2, _y_offset + squares_length/2));
	_snakes_body.push_back(std::make_pair(_x_offset + squares_length/2 - _snakes_squere_width, _y_offset + squares_length/2));
}

std::pair<int,int> Snake::DistributeAccseleration() {
	std::cout << TaskUtils::KeyPressed() << std::endl;
	switch (TaskUtils::KeyPressed()) {
	case 'W': return std::make_pair(0, -1);
	case 'S': return std::make_pair(0, 1);
	case 'A': return std::make_pair(-1, 0);
	case 'D': return std::make_pair(1, 0);
	default: return _temp_accseleration;
	}
}

std::list<std::pair<int, int>>::iterator Snake::Begin() { 
	return _snakes_body.begin(); 
}

std::list<std::pair<int, int>>::iterator Snake::End() { 
	return _snakes_body.end(); 
}

int Snake::GetSquaresLength() { 
	return _snakes_squere_width; 
}

void Snake::Push_Front(const std::pair<int, int>& pair) { 
	_snakes_body.push_front(pair); 
}

void Snake::Pop_Back() { 
	_snakes_body.pop_back();
}

std::pair<int, int> Snake::IncramentedPair()
{
	auto first_element = _snakes_body.front();
	return std::make_pair(first_element.first + (_move_per_frame * _accseleration.first), first_element.second + (_move_per_frame * _accseleration.second));
}

bool Snake::AccselerationZero() {
	return _accseleration.first == _accseleration.second && _accseleration.first == 0;
}