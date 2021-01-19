#include "table.h"
#include <vector>
#include <string>



std::vector<std::string> Table::getClub() {
	return Clubs;
}


std::vector<std::string> Table::getDia() {
	return Diamonds;
}


std::vector<std::string> Table::getHeart() {
	return Hearts;
}


std::vector<std::string> Table::getSpade() {
	return Spades;
}



void Table::playcard(std::string card) {
	char suit = card[1];
	std::string rank(1, card[0]);
	std::string uprank;
	std::string frontpile;
	std::string backpile;
	if (rank == "A") {
		uprank = "2";
	} else if (rank == "T") {
		uprank = "J";
	} else if (rank == "J") {
		uprank = "Q";
	} else if (rank == "Q") {
		uprank = "K";
	} else if (rank == "9") {
	       uprank = "T";
	} else {
		char upranktemp = card[0] + 1;
		std::string uptemp(1, upranktemp);
		uprank = uptemp;
	}
	if (suit == 'C') {
		if (Clubs.empty()) {
			Clubs.emplace_back(rank);
		} else { 
			frontpile = Clubs.front();
			backpile = Clubs.back();
			if (frontpile == backpile) {
				if (card[0] == '6') {
					Clubs.insert(Clubs.begin(), rank);
				} else {
					Clubs.emplace_back(rank);
				}
			} else if (frontpile == uprank) {
				Clubs.insert(Clubs.begin(), rank);
			} else {
				Clubs.emplace_back(rank);
			}
		}
	} else if (suit == 'H') {
		if (Hearts.empty()) {
			Hearts.emplace_back(rank);
		} else {
			frontpile = Hearts.front();
			backpile = Hearts.back();
			if (frontpile == backpile) {
				if (card[0] == '6') {
					Hearts.insert(Hearts.begin(), rank);
				} else {
					Hearts.emplace_back(rank);
				}
			} else if (frontpile == uprank) {
				Hearts.insert(Hearts.begin(), rank);
			} else {
				Hearts.emplace_back(rank);
			}
		}
	} else if (suit == 'D') {
		if (Diamonds.empty()) {
			Diamonds.emplace_back(rank);
		} else {
			frontpile = Diamonds.front();
			backpile = Diamonds.back();
			if (frontpile == backpile) {
				if (card[0] == '6') {
					Diamonds.insert(Diamonds.begin(), rank);
				} else {
					Diamonds.emplace_back(rank);
				}
			} else if (frontpile == uprank) {
				Diamonds.insert(Diamonds.begin(), rank);
			} else {
				Diamonds.emplace_back(rank);
			}
		}
	 } else {
		 if (Spades.empty()) {
			 Spades.emplace_back(rank);
		 } else {
			 frontpile = Spades.front();
			 backpile = Spades.back();
			 if (frontpile == backpile) {
				 if (card[0] == '6') {
					 Spades.insert(Spades.begin(), rank);
				 } else {
					 Spades.emplace_back(rank);
				 }
			 } else if (frontpile == uprank) {
				 Spades.insert(Spades.begin(), rank);
			 } else {
				 Spades.emplace_back(rank);
			 }
		 }
	 }
}


