#pragma once
#include <string>
#include <vector>
#include <utility>

using board_t = std::vector<std::vector<std::pair<char, Player*>>>;


struct Player {
	std::string name;
	std::string color;
	int score = 0;
};

const string defaultColor = "\033[0m";
const string bgGrey = "\033[47m";
const string red = "\033[31m";
const string blue = "\033[34m";
const string green = "\033[92m";
const string magenta = "\033[95m";
