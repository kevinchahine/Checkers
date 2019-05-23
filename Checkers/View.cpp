#include "View.h"

View::View()
{
}

View::View(size_t nRows, size_t nCols, char text, char color) :
	BaseView(nRows, nCols, text, color)
{
}

View::View(const View & view) :
	BaseView(view)
{
}

View::View(const View && view) :
	BaseView(view)
{
}

View::~View()
{
}
