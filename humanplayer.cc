#include "player.h"
#include "humanplayer.h"
#include "table.h"
#include <vector>
#include <string>
#include <algorithm>
#include "textdisplay.h"




HumanPlayer::HumanPlayer(int id, Table *t, TextDisplay *td) : Player{id, t, td} {}




void HumanPlayer::Play(std::string card) {
	std::vector<std::string>::iterator it;
	it = std::find(legal.begin(), legal.end(),card);
	if (it == legal.end()) {
		throw InvalidProcess{"This is not a legal play"};
	}  else {
		it = std::find(hands.begin(), hands.end(), card);
		hands.erase(it);
		getTable()->playcard(card);
		getTextdisplay()->printplay(this, card);
	}
}




void HumanPlayer::discards(std::string card) {
	std::vector<std::string>::iterator it;
	if (!legal.empty()) {
		throw InvalidProcess{"You have a legal play. You may not discard"};
	}  else {
		it = std::find(hands.begin(), hands.end(), card);
		if (it == hands.end()) {
			throw InvalidProcess{"Not proper card : " + card};
		}
		it = std::find(hands.begin(), hands.end(), card);
		hands.erase(it);
		discard.emplace_back(card);
		getTextdisplay()->printdiscard(this, card);
	}
}


void HumanPlayer::process() {}

