#include "CheckersManager.h"

CheckersManager::CheckersManager()
{
}

CheckersManager::~CheckersManager()
{
}

void CheckersManager::play(Player & blackPlayer, Player & redPlayer, bool showOutput)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	clock_t gameStartTime = clock();
	clock_t gameEndTime;
	int gameMoveCounter = 1;

	if (showOutput)
		print();

	bool blacksTurn = true;

	while (true)
	{
		if (status() != CheckersEngine::CONTINUE) break;

		if (showOutput)
			cout << (blacksTurn ? "BLACK" : "RED")
			<< "'s turn" << endl;

		move_t move;

		clock_t startTime = clock();
		
		if (blacksTurn)
		{
			move = blackPlayer.getDecisionAsBlack(*this);
		}

		else
			move = redPlayer.getDecisionAsRed(*this);
	
		bool jumpOccurred = movePiece(move);
		clock_t endTime = clock();
		
		// If jump did not occur, then its the opponents turn
		if (!jumpOccurred) { blacksTurn = !blacksTurn; }

		gameMoveCounter++;

		if (showOutput)
		{
			print(20, move);
		}
	}

	gameEndTime = clock();

	if (showOutput)
	{
		cout << "average move time = "
			<< (gameEndTime - gameStartTime) / gameMoveCounter / 1000.0
			<< " sec" << endl;

		cout << getEndGameMessage().str() << endl;
	}
}

stringstream CheckersManager::getEndGameMessage() const
{
	stringstream ss;

	ss << "Game Over ";

	switch (status())
	{
	case CheckersEngine::BLACK_WINS:
		ss << "Black Player Wins";
		break;
	case CheckersEngine::RED_WINS:
		ss << "Red Player Wins";
		break;
	case CheckersEngine::DRAW:
		ss << "Draw";
		break;
	default:
		ss << "Unknown game status " << status() << endl;
		break;
	}

	return ss;
}

void CheckersManager::printAnalytics(
	int nMovesSinceLastJumpOrPromotion, 
	clock_t startTime, 
	clock_t endTime, 
	clock_t gameStartTime, 
	int gameMoveCounter, 
	int heuristic, 
	HANDLE console)
{
	cout << "Moves since last jump or promotion = "
		<< nMovesSinceLastTakeOrPromotion << ' '
		<< (endTime - startTime) / 1000.0 << " sec\t"
		<< "average move time = "
		<< (endTime - gameStartTime) / gameMoveCounter / 1000.0
		<< " sec "
		<< "game duration = " << (endTime - gameStartTime) / 1000.0
		<< " sec\t"
		<< "Heuristic = ";

	uint8_t prevColor;
	Console::getColor(prevColor);

	if (heuristic > 0)
		Console::setColor(console, Colors::DARKGREY + (Colors::LIGHTGREY << 4));
	else if (heuristic < 0)
		Console::setColor(console, Colors::BLACK + (Colors::RED << 4));
	else
		Console::setColor(console, Colors::BLACK + (Colors::WHITE << 4));

	cout << heuristic << endl;

	Console::setColor(console, prevColor);
}


