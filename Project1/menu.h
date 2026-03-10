#pragma once
#include <vector>
#include <string>
class Menu
{
private:
	std::vector<std::string> options;
	int selected;
public:
	Menu(std::vector<std::string> options);
	int display();
};