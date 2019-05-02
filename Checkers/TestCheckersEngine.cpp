#include "TestCheckersEngine.h"

TestCheckersEngine::TestCheckersEngine()
{
}

TestCheckersEngine::~TestCheckersEngine()
{
}

void TestCheckersEngine::possibleMoves()
{
	this->occupied = 0;
	placePiece(3, 5, false, false);
	placePiece(4, 6, false, false);
	placePiece(2, 2, false, true);

	placePiece(5, 2, true, false);
	placePiece(6, 3, true, true);

	CheckersEngine::print();

	int r = 5;
	int c = 3;

	clock_t startTime = clock();
	vector<move_t> moves = 
		this->getValidMoves(true);
	clock_t endTime = clock();

	cout << endTime - startTime << " mSec" << endl;

	for (move_t m : moves)
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

	//cout << "Moves:" << endl << right
	//	<< setw(10) << "UpRight" << engine.isJumpUpRightPossible(r, c) << endl
	//	<< setw(10) << "UpLeftt" << engine.isJumpUpLeftPossible(r, c) << endl
	//	<< setw(10) << "DownLeft" << engine.isJumpDownLeftPossible(r, c) << endl
	//	<< setw(10) << "DownRight" << engine.isJumpDownRightPossible(r, c) << endl;

	/*cout << "Jumps:" << endl << right
		<< setw(10) << "UpRight" << this->isJumpUpRightPossible(r, c) << endl
		<< setw(10) << "UpLeftt" << this->isJumpUpLeftPossible(r, c) << endl
		<< setw(10) << "DownLeft" << this->isJumpDownLeftPossible(r, c) << endl
		<< setw(10) << "DownRight" << this->isJumpDownRightPossible(r, c) << endl;*/
}

void TestCheckersEngine::validMoves()
{
	this->occupied = 0;
	placePiece(3, 5, false, true);	// black
	placePiece(4, 4, true, true);	// red

	CheckersEngine::print();

	vector<move_t> movesBlack = this->getValidMoves(true);
	vector<move_t> movesRed = this->getValidMoves(false);

	cout << "Valid Moves BLACK" << endl;
	for (move_t m : movesBlack)
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

	cout << "Valid Moves RED" << endl;
	for (move_t m : movesRed)
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
}

void TestCheckersEngine::print() const
{
	CheckersEngine::print();
}

bool TestCheckersEngine::isPieceSafe()
{
	int8_t r = 3;
	int8_t c = 3;

	this->occupied = 0;	// remove all pieces
	
	placePiece(r, c, false, false);

	for (int8_t attackR = -1; attackR < 2; attackR += 2)
	{
		for (int8_t attackC = -1; attackC < 2; attackC += 2)
		{
			for (int8_t isBlack = 0; isBlack < 2; isBlack++)
			{
				for (int8_t isKing = 0; isKing < 2; isKing++)
				{
					placePiece(r + attackR, c + attackC, isBlack, isKing);
		
					Checkers::print(20, Move::combine(r, c, 0, c));

					if (CheckersEngine::isPieceSafe(r, c))
						cout << "Piece is safe" << endl;
					else
						cout << "Piece is being attacked" << endl;

					system("pause");

					removePiece(r + attackR, c + attackC);
				}
			}
		}
	}
	
	return false;
}

bool TestCheckersEngine::isPieceMovable()
{
	int8_t row = 3;
	int8_t col = 3;

	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			for (int c = 0; c < 2; c++)
			{
				for (int d = 0; d < 2; d++)
				{
					this->occupied = 0;	// remove all pieces

					placePiece(row, col, true, true);

					if (a == true)
						placePiece(row - 1, col + 1, true, false);
					if (b == true)
						placePiece(row - 1, col - 1, true, false);
					if (c == true)
						placePiece(row + 1, col - 1, true, false);
					if (d == true)
						placePiece(row + 1, col + 1, true, false);
					
					Checkers::print(20, Move::combine(row, col, 0, 0));

					cout << right << setw(20) << ' ';

					if (CheckersEngine::isPieceMovable(row, col))
						cout << "Piece is moveable ";
					else
						cout << "Piece is not moveable ";

					system("pause");
				}
			}
		}
	}
	
	system("pause");
	
	return false;
}

bool TestCheckersEngine::isPieceLoner()
{
	int8_t row = 3;
	int8_t col = 3;

	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			for (int c = 0; c < 2; c++)
			{
				for (int d = 0; d < 2; d++)
				{
					this->occupied = 0;	// remove all pieces

					placePiece(row, col, true, true);

					if (a == true)
						placePiece(row - 1, col + 1, true, false);
					if (b == true)
						placePiece(row - 1, col - 1, true, false);
					if (c == true)
						placePiece(row + 1, col - 1, true, false);
					if (d == true)
						placePiece(row + 1, col + 1, true, false);

					Checkers::print(20, Move::combine(row, col, 0, 0));

					cout << right << setw(20) << ' ';

					if (CheckersEngine::isPieceLoner(row, col))
						cout << "Piece is loner ";
					else
						cout << "Piece is NOT loner ";

					system("pause");
				}
			}
		}
	}

	system("pause");

	return false;
}

bool TestCheckersEngine::isSpaceAHole()
{
	int8_t row = 3;
	int8_t col = 3;

	for (int a = 0; a < 2; a++)
	{
		for (int b = 0; b < 2; b++)
		{
			for (int c = 0; c < 2; c++)
			{
				for (int d = 0; d < 2; d++)
				{
					this->occupied = 0;	// remove all pieces

					//placePiece(row, col, true, true);

					if (a == true)
						placePiece(row - 1, col + 1, true, false);
					if (b == true)
						placePiece(row - 1, col - 1, true, false);
					if (c == true)
						placePiece(row + 1, col - 1, true, false);
					if (d == true)
						placePiece(row + 1, col + 1, true, false);

					Checkers::print(20, Move::combine(row, col, 0, 0));

					cout << right << setw(20) << ' ';

					if (CheckersEngine::isSpaceAHole(row, col))
						cout << "Space is a hole ";
					else
						cout << "Space is NOT a hole ";

					system("pause");
				}
			}
		}
	}

	system("pause");

	return false;
}
