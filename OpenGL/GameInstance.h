#pragma once

//#include "CoordSys.h"
#include "Grid.h"

static class GameInstance
{
private:
	HWND* hWnd = nullptr;
	RECT window_rc;
	Grid grid;

	float dt;

public:

	GameInstance() {};

	~GameInstance()
	{
		hWnd = nullptr;
		delete hWnd;
	};

	void init(HWND* hWnd)
	{
		this->hWnd = hWnd;

		// Obtain the size of the drawing area.
		GetClientRect(
			*this->hWnd,
			&this->window_rc
		);

		this->grid = Grid(int(window_rc.right) / 5, int(window_rc.bottom) / 5, 5, 5);
	}

	int update()
	{
		grid.update();
		return 0;
	}

	int render(PAINTSTRUCT& ps)
	{

	/*	CoordSys cs = CoordSys::getInstance();

		std::cout << "initial: " << cs.getCheck() << std::endl;

		cs.setCheck(20);

		CoordSys cs2 = CoordSys::getInstance();

		std::cout << "changed: " << cs2.getCheck() << std::endl;*/

        // Save the original object
        HGDIOBJ original = SelectObject(
            ps.hdc,
            GetStockObject(DC_PEN)
        );

		grid.draw(this->window_rc, ps.hdc);

        // Restore the original object
        SelectObject(ps.hdc, original);


		return 0;
	}
};