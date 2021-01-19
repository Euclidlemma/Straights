#include <vector>
#include <string>
#include "table.h"
#include "player.h"

#include <iostream> // test purpose//


InvalidProcess::InvalidProcess(std::string message) :
	message{message}
{}



Player::Player(int id, Table *t, TextDisplay *td) :
	id{id},
	table{t},
	td{td},
	oldscore{0},
	score{0},
	det{false}
{}


Player::~Player() {};

TextDisplay * Player::getTextdisplay() {
	return td;
}

Table * Player::getTable() {
	return table;
}


void Player::addcard(std::string card) {
	if (card == "7S") {
		det = true;
	}
	hands.emplace_back(card);
}


void Player::addlegal() {
	if (det) {
		legal.emplace_back("7S");
		det = false;
	} else {
		legal.clear();
		std::vector<std::string> possiblecards;
		std::string card;
		if (!table->getClub().empty()) {
			card = table->getClub().back();
			possiblecards.emplace_back(poslegal(card + "C", true));
			card = table->getClub().front();
			possiblecards.emplace_back(poslegal(card + "C", false));
		}
		if (!table->getDia().empty()) {
			card = table->getDia().back() + "D";
			possiblecards.emplace_back(poslegal(card, true));
			card = table->getDia().front() + "D";
			possiblecards.emplace_back(poslegal(card, false));
		}
		if (!table->getHeart().empty()) {
			card = table->getHeart().back() + "H";
			possiblecards.emplace_back(poslegal(card, true));
			card = table->getHeart().front() + "H";
			possiblecards.emplace_back(poslegal(card, false));
		} 
		if (!table->getSpade().empty()) {
			card = table->getSpade().back() + "S"; 
			possiblecards.emplace_back(poslegal(card, true));
			card = table->getSpade().front() + "S";
			possiblecards.emplace_back(poslegal(card, false));
		}
		// check cards in hands, and add cards to legal if it exist in hand //
		for (auto handcard : hands) {
			if (handcard[0] == '7') {
					legal.emplace_back(handcard);
			} else {
				for (auto c: possiblecards) {
					if (c == handcard) {
						legal.emplace_back(handcard);
					}
				}
			}
		}
	}
}



std::string poslegal(std::string card, bool up) {
	char suit = card[1];
	char rank = card[0];
	std::string adjacent(2,suit);
	if (rank == 'T') {
		if (!up) {
			adjacent[0] = '9';
		} else {
			adjacent[0] = 'J';
		}
	} else if (rank == 'J') {
		if (!up) {
			adjacent[0] = 'T';
		} else {
			adjacent[0] = 'Q';
		}
	} else if (rank == 'Q') {
		if (!up) {
			adjacent[0] = 'J';
		} else {
			adjacent[0] = 'K';
		}
	} else if (rank == 'K') {
		if (!up) {
			adjacent[0] = 'Q';
		} else {
			adjacent = "false";
		}
	} else if (rank == 'A') {
		if (!up) {
			adjacent = "false";
		} else {
			adjacent[0] = '2';
		}
	} else if (rank == '9') {
		if (!up) {
			adjacent[0] = '8';
		} else {
			adjacent[0] = 'T';
		}
	} else if (rank == '2') {
		if (!up) {
			adjacent[0] = 'A';
		} else {
			adjacent[0] = '3';
		}
	} else {
		if (!up) {
			adjacent[0] = rank  - 1;
		} else {
			adjacent[0] = rank + 1;
		}
	}
	return adjacent;
}



std::vector<std::string> Player::gethands() const {
	return hands;
}


std::vector<std::string> Player::getdiscard() const {
	return discard;
}


std::vector<std::string> Player::getlegal() const {
	return legal;
}



int Player::getid() const {
	return id;
}


int Player::getoldscore() const{
	return oldscore;
}

int Player::getscore() const {
	return score;
}


bool Player::getdet() const {
	return det;
}


void Player::scoring() {
	oldscore = score;
	int curscore = score;
	for (auto card : discard) {
		char rank = card[0];
		if (rank == 'A') {
			curscore = curscore + 1;
		} else if (rank == 'T') {
			curscore = curscore + 10;
		} else if (rank == 'J') {
			curscore = curscore + 11;
		} else if (rank == 'Q') {
			curscore = curscore + 12;
		} else if (rank == 'K') {
			curscore = curscore + 13;
		} else {
			int rankint = rank - '0';
			curscore = curscore + rankint;
		}
	}
	score = curscore;
}
