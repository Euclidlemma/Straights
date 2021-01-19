#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include "humanplayer.h"
#include "strategy.h"
#include <vector>
#include <string>

class Strategy;


class ComputerPlayer: public Player {
	std::vector<Strategy*> strategies;
	public:
	int stratindex;
	void hptocp(Player *p);
	ComputerPlayer(int id, Table *t, TextDisplay *td);
	void setstrategy(std::vector<Strategy*> strats);
	void Play(std::string card) override;
	void discards(std::string card) override;
	void process() override;
	friend class Strategy;
};

#endif
