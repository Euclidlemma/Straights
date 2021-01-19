#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>
#include "computerplayer.h"

class ComputerPlayer;

class Strategy {
	public:
	virtual std::string stratplay(ComputerPlayer *c) = 0;
	virtual std::string stratdiscard(ComputerPlayer *c) = 0;
};

#endif

