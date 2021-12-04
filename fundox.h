#pragma once
#include <string>
#include <vector>
#include <utility>

using board_t = std::vector<std::vector<std::pair<char, std::string>>>;

struct Player {
	std::string name;
	std::string color;
	int score = 0;
};

