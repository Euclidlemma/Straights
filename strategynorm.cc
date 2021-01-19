#include <vector>
#include <string>
#include "strategynorm.h"
#include "strategy.h"
#include "computerplayer.h"


std::string StrategyNorm::stratplay(ComputerPlayer* c) {
	return c->getlegal()[0];
}


std::string StrategyNorm::stratdiscard(ComputerPlayer* c) {
	return c->gethands()[0];
}


