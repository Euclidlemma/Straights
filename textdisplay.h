#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "table.h"
#include <vector>
#include <string>


class Player;

class TextDisplay {
	public:
	void printtable(Table *t);
	void printplayer(Player *p);
	void printplay(Player *p, std::string card);
	void printdiscard(Player *p, std::string card);
	void printscore(Player *p);
	void printwinner(std::vector<int> winners);
};

void print(std::vector<std::string> pile);

#endif

