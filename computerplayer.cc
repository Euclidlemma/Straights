#include "computerplayer.h"
#include <vector>
#include <string>
#include <algorithm>
#include "player.h"
#include "humanplayer.h"



ComputerPlayer::ComputerPlayer(int id, Table *t, TextDisplay *td) :
       Player{id, t, td},
       stratindex{0}
{}


void ComputerPlayer::hptocp(Player *p) {
	hands = p->gethands();
	discard = p->getdiscard();
	legal = p->getlegal();
	oldscore = p->getoldscore();
	score = p->getscore();
	det = p->getdet();
	delete p;
}





void ComputerPlayer::setstrategy(std::vector<Strategy*> strats) {
	strategies = strats;
}



void ComputerPlayer::Play(std::string card) {
	return;
}


void ComputerPlayer::discards(std::string card) {
	return;
}


void ComputerPlayer::process() {
	std::vector<std::string>::iterator it;
	std::string retcard;
	if (legal.empty()) {
		retcard = strategies[stratindex]->stratdiscard(this);
		it = std::find(hands.begin(), hands.end(), retcard);
		hands.erase(it);
		discard.emplace_back(retcard);
		getTextdisplay()->printdiscard(this, retcard);
		// must add to manipulae textdisplay//
	} else {
		retcard = strategies[stratindex]->stratplay(this);
		it = std::find(hands.begin(), hands.end(), retcard);
		hands.erase(it);
		getTable()->playcard(retcard);
		getTextdisplay()->printplay(this, retcard);
	}
}


