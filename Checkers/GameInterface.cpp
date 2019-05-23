#include "GameInterface.h"

GameInterface::GameInterface() :
	layout(BaseView(N_ROWS_DEFAULT, N_COLS_DEFAULT, 'X'))
{}

GameInterface::GameInterface(const ViewLayout & layout) :
	layout(layout)
{
}

GameInterface::GameInterface(const ViewLayout && layout) :
	layout(layout)
{
}

GameInterface::GameInterface(const GameInterface & gameInterface) :
	layout(gameInterface.layout)
{
}

GameInterface::GameInterface(const GameInterface && gameInterface) :
	layout(gameInterface.layout)
{
}

GameInterface::~GameInterface()
{
}

void GameInterface::print() const
{
	layout.print();
}
