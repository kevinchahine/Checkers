#pragma once

#include <iostream>
#include <iomanip>
#include <tuple>
#include <vector>
#include <list>

#include "E:\Documents\Programming\C++\ASCII\ASCII\ASCII.h"
#include "Colors.h"
#include "Console.h"
#include "BaseView.h"
#include "View.h"

using namespace std;

class ViewLayout : public BaseView
{
public:
	ViewLayout();
	ViewLayout(const BaseView & baseView);
	ViewLayout(const BaseView && baseView);
	ViewLayout(const ViewLayout & viewLayout);
	ViewLayout(const ViewLayout && viewLayout);
	~ViewLayout();

	void stamp(const BaseView & view, size_t row, size_t col);
	
	void print();

protected:
	// Each element points to a color_text_t value in a 
	// View object
	vector<vector<const View::color_text_t *>> colorTextPtr;
};

