#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <memory>
#include <random>

#include "humanplayer.h"
#include "computerplayer.h"
#include "player.h"
#include "strategy.h"
#include "strategynorm.h"
#include "textdisplay.h"
#include "table.h"


// endgame detremineds whether players in the vector are able to end the game//
bool endgame(std::vector<Player*> players) {
	for (int index = 0; index < 4; index++) {
		if(players[index]->getscore() >= 80) {
			return true;
		}
	}
	return false;
}


// firstplayerind returns index of the player who has 7S card//
int firstplayerind(std::vector<Player*> players) {
	for (int i = 0; i < 4; i++) {
		if (players[i]->getdet()) {
			return i;
		}
	}
	return 0;
}



bool endround(std::vector<Player*> players) {
	for (int index = 0; index < 4; index++) {
		if (!players[index]->gethands().empty()) {
			return false;
		}
	}
	return true;
}




int main(int argc, char **argv) {
	bool properquit = true;
	unsigned seed = 0;
	if (argc >= 2) {
		std::istringstream seedstream{argv[1]};
		seedstream >> seed;
	}
	std::string suit[] = {"C", "D", "H", "S"};
	std::string rank[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
	std::vector<std::string> ordinarydeck;
	for (int c = 0; c < 4; c++) {
		for (int b = 0; b < 13; b++) {
			std::string card = rank[b] + suit[c];
			ordinarydeck.emplace_back(card);
		}
	}
	std::vector<std::string> shuffleddeck = ordinarydeck;
	std::string s;
	std::vector<Player *> players;
	Table *t = new Table{};
	TextDisplay td = TextDisplay{};
	//constructing strategies//
	std::vector<Strategy*> strats;
	StrategyNorm normalstrat{};
	strats.emplace_back(&normalstrat);


	std::vector<int> computer; //saves index of the computer players//
	//setup players//
	for (int i = 1; i <= 4; i++) {
		std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
		std::cin >> s;
		std::istringstream isssetup{s};
		std::string playercmd;
		isssetup >> playercmd;
		if (playercmd == "h") {
			players.emplace_back(new HumanPlayer{i, t, &td});
		} else if (playercmd == "c") {
			ComputerPlayer *cp = new ComputerPlayer{i, t, &td};
			computer.emplace_back(i);
			cp->setstrategy(strats);
			players.emplace_back(cp);
		} else {
			std::cout << "Wrong Command" << std::endl;
			i--;
		}
	}
	bool gameend = false;

	while (!gameend){
		if (endgame(players)) {
			gameend = true;
			break;
		}
		shuffle(shuffleddeck.begin(), shuffleddeck.end(), std::default_random_engine(seed));
		int cardindex = 0;
		for (int index = 0; index < 4; index++) {
			for (int number = 0; number < 13; number++) {
				players[index]->addcard(shuffleddeck[cardindex]);
				cardindex++;
			}
		}
		int turn = firstplayerind(players);
		bool cp = false;
		bool roundend = false;
		std::cout << "A new round begins. It's Player" << players[turn]->getid() << "'s turn to play." << std::endl;
		while(!roundend) {
			if (endround(players)) {
				roundend = true;
				break;
			}
			if (turn == 4) {
				turn = 0;
			}
			//check if this turn is computer or not
			for (auto n : computer) {
				if (turn+1 == n) {
					cp = true;
					break;
				}
			} 
			players[turn]->addlegal();
			if (cp) {
				players[turn]->process();
				turn++;
				cp = false;
			} else {
				td.printtable(t);
				td.printplayer(players[turn]);
				while(std::getline(std::cin, s)) {
					std::istringstream iss{s};
					std::string cmd;
					iss >> cmd;
					if ("play" == cmd) {
						std::string incard;
						iss >> incard;
						try {
							players[turn]->Play(incard);
							break;
						} catch (InvalidProcess &i) {
							std::cout << i.message << std::endl;
							continue;
						}
					} else if ("discard" == cmd) {
						std::string disincard;
						iss >> disincard;
						try {
							players[turn]->discards(disincard);
							break;
						} catch (InvalidProcess &i) {
							std::cout << i.message << std::endl;
							continue;
						}
					} else if ("deck" == cmd) {
						int cardnum = 0;
						for (auto deckcard : shuffleddeck) {
							std::cout << deckcard;
							if (cardnum == 12) {
								std::cout << '\n';
								cardnum = 0;
							} else {
								std::cout << " ";
								cardnum++;
							}
						}
						continue;
					} else if ("quit" == cmd) {
						gameend = true;
						roundend = true;
						properquit = false;
						break;
					} else if ("quittest" == cmd) {
						gameend = true;
						roundend = true;
						break;
					} else if ("ragequit" == cmd) {
						std::cout << "Player" << turn+1 << " ragequits. A computer will now take over." << std::endl;
						computer.emplace_back(players[turn]->getid());
						ComputerPlayer *newcp = new ComputerPlayer(players[turn]->getid(), t, &td);
						newcp->hptocp(players[turn]);
						newcp->setstrategy(strats);
						newcp->process();
						players[turn] = newcp;
						break;
					} else if (cmd != "") {
						std::cout << "Wrong Command" << std::endl;
						continue;
					}
				}
				turn++;
			}
		} // round end//
		if (properquit) {
			for (int iter = 0; iter < 4; iter++) {
				players[iter]->scoring();
				td.printscore(players[iter]);
			}
			shuffleddeck = ordinarydeck;
		}
	} // gameend//

	//determining winner//
	if (properquit) {
		std::vector<int> winners;
		int minscore = 0;
		for (int x = 0; x < 4; x++) {
			int playerscore = players[x]->getscore();
			int playid = players[x]->getid();
			if (x == 0) {
				minscore = players[x]->getscore();
				winners.emplace_back(playid);
			} else {
				if (minscore > playerscore) {
					winners.clear();
					minscore = playerscore;
					winners.emplace_back(playid);
				} else if (minscore == playerscore) {
					winners.emplace_back(playid);
				}
			}
		}
		td.printwinner(winners);
	}
	for (auto p : players) {
		delete p;
	}
	delete t;
}

					







		

