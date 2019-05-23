#pragma once

#include <iostream>
#include <iomanip>
#include <tuple>
#include <vector>
#include <list>

#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "Colors.h"
#include "Console.h"

using namespace std;

class BaseView
{
public:
	BaseView();
	BaseView(size_t nRows, size_t nCols, char text = ' ', char color = 15);
	BaseView(const BaseView & baseView);
	BaseView(const BaseView && baseView);
	~BaseView();

	virtual void print();

	typedef pair<char, char> color_text_t;

	vector<vector<color_text_t>> colorText;
};

