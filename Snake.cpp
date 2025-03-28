#include "Snake.h"
#include "TaskUtils.h"

Snake::Snake(int x_offset, int y_offset, int squares_length, int _FPS) {
	_move_per_frame = _FPS / _snakes_square_width * _speed;
	_x_start = 0;
	_y_start = 0;

	_x_offset = x_offset;
	_y_offset = y_offset;

	_accseleration = std::make_pair(0, 0);
	_temp_accseleration = std::make_pair(0, 0);

	_snakes_body.push_back(std::make_pair(_x_offset + squares_length/2 + _snakes_square_width/2, _y_offset + squares_length/2 + _snakes_square_width/2));
	_snakes_body.push_back(std::make_pair(_x_offset + squares_length/2, _y_offset + squares_length/2 + _snakes_square_width/2));
}

std::pair<int,int> Snake::DistributeAccseleration() {
	char key_pressed = TaskUtils::KeyPressed();
	std::pair<int, int> temp;

	if ((key_pressed == 'W' || key_pressed == '&') && _temp_accseleration != std::make_pair(0,1)){
		temp =  std::make_pair(0, -1);
	}
	else if ((key_pressed == 'S' || key_pressed == '(') && _temp_accseleration != std::make_pair(0,-1)) {
		temp =  std::make_pair(0, 1);
	}
	else if ((key_pressed == 'A' || key_pressed == '%') && _temp_accseleration != std::make_pair(1,0)){
		temp = std::make_pair(-1, 0);
	}
	else if ((key_pressed == 'D' || key_pressed == '\'') && _temp_accseleration != std::make_pair(-1,0)){
		temp = std::make_pair(1, 0);
	}
	else {
		return _temp_accseleration;
	}
	if (!GoingBackwards(temp))
		return temp;

	return _temp_accseleration;
}

std::list<std::pair<int, int>>::iterator Snake::Begin() { 
	return _snakes_body.begin(); 
}

std::list<std::pair<int, int>>::iterator Snake::End() { 
	return _snakes_body.end(); 
}

int Snake::GetSquaresLength() { 
	return _snakes_square_width; 
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

int Snake::HeadHitApple(const ApplesInformation* apples) {
	for (size_t i = 0; i < apples->_coordinates.size(); i++) {
		if (_snakes_body.front().first - _x_offset == apples->_coordinates[i].first && _snakes_body.front().second - _y_offset == apples->_coordinates[i].second) {
			return i;
		}
	}
	return -1;
}

bool Snake::GoingBackwards(const std::pair<int, int>& pair) {
	auto first_element = _snakes_body.front();
	if (std::make_pair(first_element.first + (_move_per_frame * pair.first), first_element.second + (_move_per_frame * pair.second)) == *std::next(_snakes_body.begin())) {
		return true;
	}
	return false;
}

bool Snake::OutOfBounds(int squares_width) {
	auto first_element = _snakes_body.front();

	if (first_element.first - _x_offset < 0 || first_element.second - _y_offset < 0) {
		return true;
	}
	else if ((first_element.first + _snakes_square_width) > squares_width + _x_offset || (first_element.second + _snakes_square_width) > squares_width + _y_offset) {
		return true;
	}
	return false;
}

bool Snake::HitItself() {
	auto front = _snakes_body.front();

	for (auto it = std::next(_snakes_body.begin()); it != _snakes_body.end(); it++) {
		if (front == *it)
			return true;
	}
	return false;
}