#ifndef PLAYER_H
#define PLAYER_H


#include <vector>
#include <string>
#include <iostream>
#include "table.h"
#include "textdisplay.h"


struct InvalidProcess {
	std::string message;
	InvalidProcess(std::string message);
};



class Player {
	int id;
	Table *table;
	TextDisplay *td;
	protected:
	std::vector<std::string> hands;
	std::vector<std::string> discard;
	std::vector<std::string> legal;
	TextDisplay * getTextdisplay();
	Table * getTable();
	int oldscore;
	int score;
	bool det;
	Player(int id, Table *t, TextDisplay *td);
	public:
	virtual ~Player();
	void addcard(std::string card);
	void addlegal();
	std::vector<std::string> gethands() const;
	std::vector<std::string> getdiscard() const;
	std::vector<std::string> getlegal() const;
	int getid() const;
	int getoldscore() const;
	int getscore() const;
	bool getdet() const;
	void scoring();
	virtual void Play(std::string card) = 0;
	virtual void discards(std::string card) = 0;
	virtual void process() = 0;
};


std::string poslegal(std::string card, bool up);

#endif


