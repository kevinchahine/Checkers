#include "User.h"

User::User() {}

User::~User()
{
}

move_t User::getDecision(const CheckersEngine & game, bool isBlack) const
{
	vector<move_t> validMoves = game.getValidMoves(isBlack);

	move_t move;
	int fromRow;
	int fromCol;
	int toRow;
	int toCol;

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
		move = Move::combine(fromRow, fromCol, toRow, toCol);

		// 4.) See if move is valid
		vector<move_t>::const_iterator it =
			find(validMoves.begin(), validMoves.end(), move);

		if (it == validMoves.end())
			continue;	// Move is not valid
		else
			break;		// Move is valid
	}

	return move;
}

move_t User::getDecisionAsBlack(const CheckersEngine & game) const
{
	return getDecision(game, true);
}

move_t User::getDecisionAsRed(const CheckersEngine & game) const
{
	return getDecision(game, false);
}
