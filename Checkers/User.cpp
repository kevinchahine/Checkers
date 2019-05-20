#include "User.h"

User::User() {}

User::~User()
{
}

move_t User::getDecision(const CheckersEngine & game, COLOR asPlayer) const
{
	return move_t();
}

move_t User::getDecisionAsBlack(const CheckersEngine & game) const
{
	cerr << "Method not implemented" << __FILE__ << " line " << __LINE__ << endl;
	return -1;
}

move_t User::getDecisionAsRed(const CheckersEngine & game) const
{
	cerr << "Method not implemented" << __FILE__ << " line " << __LINE__ << endl;
	return -1;
}
