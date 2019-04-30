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
	vector<CheckersEngine::move_t> moves = 
		this->getValidMoves(true);
	clock_t endTime = clock();

	cout << endTime - startTime << " mSec" << endl;

	for (CheckersEngine::move_t m : moves)
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

	vector<CheckersEngine::move_t> movesBlack = this->getValidMoves(true);
	vector<CheckersEngine::move_t> movesRed = this->getValidMoves(false);

	cout << "Valid Moves BLACK" << endl;
	for (CheckersEngine::move_t m : movesBlack)
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
	for (CheckersEngine::move_t m : movesRed)
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
