#pragma once

#include <iostream>
#include <iomanip>
#include <tuple>
#include <vector>

#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "BaseView.h"
#include "Colors.h"
#include "Console.h"

using namespace std;

class View : public BaseView
{
public:
	View();
	View(size_t nRows, size_t nCols, char text = ' ', char color = 15);
	View(const View & view);
	View(const View && view);
	~View();
	
};

