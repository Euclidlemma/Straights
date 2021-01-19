#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>


class Table {
	std::vector<std::string> Clubs;
	std::vector<std::string> Diamonds;
	std::vector<std::string> Hearts;
	std::vector<std::string> Spades;
	public: 
	std::vector<std::string> getClub();
	std::vector<std::string> getDia();
	std::vector<std::string> getHeart();
	std::vector<std::string> getSpade();
	void playcard(std::string card);
};


#endif

