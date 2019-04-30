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


