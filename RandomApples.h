#ifndef RANDOMAPLLES_H
#define RANDOMAPPLES_H

#include <vector>
#include <utility>

class ApplesInformation {
private:
	//std::vector<std::pair<int, int>> _coordinates;
	bool Contains(const std::pair<int, int>& pair);
	bool Equals(const std::pair<int, int>& left, const std::pair<int, int>& right);

	int _width;
	int _height;
public:
	std::vector<std::pair<int, int>> _coordinates;
	int _index;
	int _count;

	ApplesInformation(size_t n, int width);
	~ApplesInformation();
	void GenerateNApples();
};

#endif
