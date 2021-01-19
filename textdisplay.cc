#include "textdisplay.h"
#include "player.h"
#include "table.h"
#include <vector>
#include <string>
#include <iostream>



void TextDisplay::printtable(Table *t) {
	std::cout << "Cards on the table:\n";
	std::cout << "Clubs:";
	print(t->getClub());
	std::cout << std::endl;
	std::cout << "Diamonds:";
	print(t->getDia());
	std::cout << std::endl;
	std::cout << "Hearts:";
	print(t->getHeart());
	std::cout << std::endl;
	std::cout << "Spades:";
	print(t->getSpade());
	std::cout << std::endl;
}


void TextDisplay::printplayer(Player *p) {
	std::cout << "Your hand:";
	print(p->gethands());
	std::cout << std::endl;
	std::cout << "Legal plays:";
	print(p->getlegal());
	std::cout << std::endl;
}



void TextDisplay::printplay(Player *p, std::string card) {
	std::cout << "Player" << p->getid() << " " << "plays " << card << std::endl;
}



void TextDisplay::printdiscard(Player *p, std::string card) {
	std::cout << "Player" << p->getid() << " " << "discards " << card << std::endl;
}



void TextDisplay::printscore(Player *p) {
	std::cout << "Player" << p->getid() << "'s discards:";
	print(p->getdiscard());
	std::cout << std::endl;
	std::cout << "Player" << p->getid() << "'s score: " << p->getoldscore() << " + " << p->getscore() - p->getoldscore() << " = " << p->getscore() << std::endl;
}


void TextDisplay::printwinner(std::vector<int> winners) {
	for (auto n: winners) {
		std::cout << "Player" << n << " wins!" << std::endl;
	}
}

void print(std::vector<std::string> pile) {
	for (auto card : pile) {
		std::cout << " " << card;
	}
}



