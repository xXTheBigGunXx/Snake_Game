#ifndef RANDOMAPLLES_H
#define RANDOMAPPLES_H

#include <vector>
#include <utility>

class ApplesInformation {
private:
	std::vector<std::pair<int, int>> _coordinates;
	void GenerateNApples(size_t n);
	bool Contains(const std::pair<int, int>& pair);
	bool Equals(const std::pair<int, int>& left, const std::pair<int, int>& right);
public:
	ApplesInformation(size_t n = 0);
	~ApplesInformation();
};

#endif
