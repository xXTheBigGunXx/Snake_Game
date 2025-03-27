#include "RandomApples.h"
#include "TaskUtils.h"

ApplesInformation::ApplesInformation(size_t n, int width): _index(0), _count(n), _width(width) {}

ApplesInformation::~ApplesInformation() {
	_coordinates.clear();
}

void ApplesInformation::GenerateNApples() {
	for (; _index < _count; _index++){
		std::pair<int, int> coords(TaskUtils::RandomInt(_width), TaskUtils::RandomInt(_width));
		if (Contains(coords)) {
			_index--;
			continue;
		}
		_coordinates.push_back(coords);
	}
}

bool ApplesInformation::Contains(const std::pair<int, int>& pair) {
	for (size_t i = 0; i < _coordinates.size(); i++) {
		if (Equals(_coordinates.at(i), pair)) {
			return true;
		}
	}
	return false;
}

bool ApplesInformation::Equals(const std::pair<int, int>& left, const std::pair<int, int>& right) {
	return left.first == right.first && left.second == right.second;
}