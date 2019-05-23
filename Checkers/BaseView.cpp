#include "BaseView.h"

BaseView::BaseView()
{
}

BaseView::BaseView(size_t nRows, size_t nCols, char text, char color) :
	colorText(nRows,
		vector<color_text_t>(nCols,
			color_text_t(color, text)))
{
}

BaseView::BaseView(const BaseView & baseView) :
	colorText(baseView.colorText)
{
}

BaseView::BaseView(const BaseView && baseView) :
	colorText(baseView.colorText)
{
}

BaseView::~BaseView()
{
}

void BaseView::print()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// Save original console color
	uint8_t consoleColor;
	Console::getColor(consoleColor);

	for (const vector<color_text_t> & row : this->colorText)
	{
		for (color_text_t col : row)
		{
			// Set Color
			Console::setColor(console, col.first);

			// Print Char
			cout << col.second;
		}
		cout << endl;
	}
	cout << endl;

	// Restore original console color
	Console::setColor(console, consoleColor);
}
