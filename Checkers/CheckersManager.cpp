#include "CheckersManager.h"

CheckersManager::CheckersManager()
{
}

CheckersManager::~CheckersManager()
{
}

void CheckersManager::playUserVsComputer()
{
}

void CheckersManager::playUserVsUser()
{
	int fromRow, fromCol, toRow, toCol;

	typedef vector<CheckersEngine::move_t> moves_t;
	moves_t possibleMoves;

	bool blacksTurn = true;

	while (true)
	{
		if (gamePtr->status() != CheckersEngine::CONTINUE) break;

		possibleMoves = gamePtr->getValidMoves(blacksTurn);

		// Show valid moves
		for (auto m : possibleMoves)
		{
			int fromRow = (m >> 12) & 0x0f;
			int fromCol = (m >> 8) & 0x0f;
			int toRow = (m >> 4) & 0x0f;
			int toCol = m & 0x0f;
			cout << m << "["
				<< fromRow << ", " << fromCol << "]->["
				<< toRow << ", " << toCol << "]"
				<< endl;
		}

		gamePtr->print();
		cout << "Moves since last jump or promotion = "
			<< gamePtr->nMovesSinceLastTakeOrPromotion << endl;

		cout << (blacksTurn ? "BLACK" : "RED") << ' ';
			
		getUserInput(fromRow, fromCol, toRow, toCol, possibleMoves);

		bool jumpOccurred = 
			gamePtr->movePiece(fromRow, fromCol, toRow, toCol);

		// If jump occurred, then its the same players turn
		if (jumpOccurred)	{	}
		else				{ blacksTurn = !blacksTurn; }
	}

	gamePtr->print();
	cout << getEndGameMessage().str() << endl;
}

void CheckersManager::playComputerVsUser()
{
}

void CheckersManager::playComputerVsComputer()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	
	clock_t gameStartTime = clock();
	clock_t gameEndTime;
	int gameMoveCounter = 1;

	gamePtr->print();

	CheckersSolver solver;
	
	bool blacksTurn = true;

	while (true)
	{
		if (gamePtr->status() != CheckersEngine::CONTINUE) break;

		cout << (blacksTurn ? "BLACK" : "RED") << "'s turn" << endl;

		pair<bool, Checkers::move_t> ret;

		clock_t startTime = clock();
		if (blacksTurn) ret = solver.playAsBlack(*gamePtr);
		else			ret = solver.playAsRed(*gamePtr);
		clock_t endTime = clock();
		gameMoveCounter++;

		bool jumpOccurred;
		jumpOccurred = ret.first;

		// If jump occurred, then its the same players turn
		if (jumpOccurred) {}
		else { blacksTurn = !blacksTurn; }
		
		Checkers::move_t move = ret.second;

		gamePtr->print(20, move);

		cout << "Moves since last jump or promotion = "
			<< gamePtr->nMovesSinceLastTakeOrPromotion << ' '
			<< (endTime - startTime) / 1000.0 << " sec\t"
			<< "average move time = "
			<< (endTime - gameStartTime) / gameMoveCounter / 1000.0
			<< " sec\t"
			<< "Heuristic = ";
		
		uint8_t prevColor;
		Console::getColor(prevColor);

		int h = solver.heuristic(*gamePtr);
		if (h > 0)
			Console::setColor(console, Colors::DARKGREY + (Colors::LIGHTGREY << 4));
		else if (h < 0)
			Console::setColor(console, Colors::BLACK + (Colors::RED << 4));
		else
			Console::setColor(console, Colors::BLACK + (Colors::WHITE << 4));

		cout << h << endl;
		Console::setColor(console, prevColor);

		///system("pause");
	}

	gameEndTime = clock();
	cout << "average move time = "
		<< (gameStartTime - gameEndTime) / gameMoveCounter / 1000.0
		<< " sec" << endl;

	///gamePtr->print();
	cout << getEndGameMessage().str() << endl;
}

stringstream CheckersManager::getEndGameMessage() const
{
	stringstream ss;

	ss << "Game Over ";

	switch (gamePtr->status())
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
		ss << "Unknown game status " << gamePtr->status() << endl;
		break;
	}

	return ss;
}

CheckersEngine::move_t CheckersManager::getUserInput(
	int & fromRow, int & fromCol, int & toRow, int & toCol, 
	const vector<CheckersEngine::move_t>& validMoves) const
{
	CheckersEngine::move_t move;

	char fromRowChar, fromColChar, toRowChar, toColChar;
	
	while (true)
	{
		cout << "Enter: ";

		// 1.) Read input
		cin >> fromColChar >> fromRowChar >> toColChar >> toRowChar;
		string s;
		getline(cin, s);

		// 2.) Convert to numerical coordinates
		if (isalpha(fromColChar) && !isalpha(fromRowChar))
		{
			fromColChar = toupper(fromColChar);
			fromCol = fromColChar - 'A';

			fromRow = fromRowChar - '1';
		}
		else
		{
			continue;
		}

		if (isalpha(toColChar) && !isalpha(toRowChar))
		{
			toColChar = toupper(toColChar);
			toCol = toColChar - 'A';

			toRow = toRowChar - '1';
		}
		else
		{
			continue;
		}

		cout << "Move = " << fromRow << " " << fromCol << " -> "
			<< toRow << ' ' << toCol << endl;

		// 3.) Calc move
		move =
			(fromRow << 12) |
			(fromCol << 8) |
			(toRow << 4) |
			(toCol);

		// 4.) See if move is valid
		vector<CheckersEngine::move_t>::const_iterator it =
			find(validMoves.begin(), validMoves.end(), move);

		if (it == validMoves.end())
			continue;	// Move is not valid
		else
			break;		// Move is valid


	}

	return move;
}


