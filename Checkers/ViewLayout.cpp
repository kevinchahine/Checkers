#include "ViewLayout.h"

ViewLayout::ViewLayout() {}

ViewLayout::ViewLayout(const BaseView & baseView) :
	BaseView(baseView),
	colorTextPtr(
		baseView.colorText.size(), 
		vector<const View::color_text_t *>(
			baseView.colorText.front().size(), nullptr))
{
}

ViewLayout::ViewLayout(const BaseView && baseView) :
	BaseView(baseView),
	colorTextPtr(
		baseView.colorText.size(),
		vector<const View::color_text_t *>(
			baseView.colorText.front().size(), nullptr))
{
}

ViewLayout::ViewLayout(const ViewLayout & viewLayout) :
	BaseView(viewLayout),
	colorTextPtr(viewLayout.colorTextPtr)
{
}

ViewLayout::ViewLayout(const ViewLayout && viewLayout) :
	BaseView(viewLayout),
	colorTextPtr(viewLayout.colorTextPtr)
{
}

ViewLayout::~ViewLayout()
{
}

void ViewLayout::stamp(const BaseView & view, size_t row, size_t col)
{
	if (typeid(view) == typeid(View))
	{
		const View & v = dynamic_cast<const View &>(view);

		const size_t ROW_CUTOFF =
			min(v.colorText.size(),
				max((int) colorTextPtr.size() - (int) row, 0));

		for (size_t r = 0; r < ROW_CUTOFF; r++)
		{
			const vector<color_text_t> & vRow =
				v.colorText.at(r);

			const size_t COL_CUTOFF =
				min(vRow.size(),
					max((int) colorTextPtr.size() - (int) col, 0));

			for (size_t c = 0; c < COL_CUTOFF; c++)
			{
				colorTextPtr.at(r + row).at(c + col) = 
					&(vRow.at(c));
			}
		}
	}
	else if (typeid(view) == typeid(ViewLayout))
	{
		const ViewLayout & v = dynamic_cast<const ViewLayout &>(view);

		const size_t ROW_CUTOFF =
			min(v.colorText.size(),
				max((int)colorTextPtr.size() - (int)row, 0));

		for (size_t r = 0; r < ROW_CUTOFF; r++)
		{
			const vector<color_text_t> & vRow =
				v.colorText.at(r);

			const size_t COL_CUTOFF =
				min(vRow.size(),
					max((int)colorTextPtr.size() - (int)col, 0));

			for (size_t c = 0; c < COL_CUTOFF; c++)
			{
				const color_text_t * ptr = v.colorTextPtr.at(r).at(c);

				if (ptr == nullptr)
					ptr = &v.colorText.at(r).at(c);

				colorTextPtr.at(r + row).at(c + col) = ptr;
			}
		}
	}
}

void ViewLayout::print()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	// Save original console color
	uint8_t consoleColor;
	Console::getColor(consoleColor);

	for (size_t r = 0; r < colorTextPtr.size(); r++)
	{
		for (size_t c = 0; c < colorTextPtr.at(r).size(); c++)
		{
			const color_text_t * tPtr = colorTextPtr.at(r).at(c);
			
			if (tPtr == nullptr)
			{
				tPtr = &colorText.at(r).at(c);
			}

			char color = tPtr->first;
			char text = tPtr->second;
			
			// Set Color
			Console::setColor(console, color);
			
			// Print Char
			cout << text;
		}
		cout << endl;
	}
	cout << endl;

	// Restore original console color
	Console::setColor(console, consoleColor);
}
