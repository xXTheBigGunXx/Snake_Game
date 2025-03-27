#ifndef RANDOMAPLLES_H
#define RANDOMAPPLES_H

#include <vector>
#include <utility>

class ApplesInformation {
private:
	//std::vector<std::pair<int, int>> _coordinates;
	void GenerateNApples();
	bool Contains(const std::pair<int, int>& pair);
	bool Equals(const std::pair<int, int>& left, const std::pair<int, int>& right);
	int _index;
	int _count;
public:
	std::vector<std::pair<int, int>> _coordinates;
	ApplesInformation(size_t n);
	~ApplesInformation();
};

#endif
