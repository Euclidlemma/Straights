#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H



#include <vector>
#include<string>
#include <iostream>
#include "player.h"
#include "table.h"
#include "textdisplay.h"


class HumanPlayer:public Player {
	public:
	HumanPlayer(int id, Table *t, TextDisplay *td);
	void Play(std::string card) override;
	void discards(std::string card) override;
	void process() override;
};

#endif

