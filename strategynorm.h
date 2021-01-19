#ifndef STRATEGYNORM_H
#define STRATEGYNORM_H

#include <string>
#include <vector>
#include "computerplayer.h"
#include "strategy.h"


class StrategyNorm : public Strategy {
	public:
	std::string stratplay(ComputerPlayer *c) override;
	std::string stratdiscard(ComputerPlayer *c) override;
};

#endif 

