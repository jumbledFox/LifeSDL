#include <string>
#include <iostream>
#include <stdlib.h>
#include <memory>

#include "CellMap.h"

#include "include/SDL.h"

namespace Life {
	
	CellMap::CellMap(unsigned int width, unsigned int height) : w(width), h(height) {

		srand(time(NULL));

		length = w * h;
		cells = new unsigned char[length];
		cellsBuffer = new unsigned char[length];

		memset(cells, 0, length);
		
		for (int i = 0; i < length; i++) {
			if (rand() % 3) { SetCell(i, true); }
		}

		/*
		std::pair<int, int> defaults[] = { {0, 2}, {1, 2}, {2, 2}, {2, 1}, {1, 0} };
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				for (const auto& p : defaults) {
					SetCell(p.first + (x * 10), p.second + (y * 10), true);
				}
			}
		}
		*/
	}

	CellMap::~CellMap() {
		delete[] cells;
		delete[] cellsBuffer;
	}

	void CellMap::SetCell(unsigned int x, unsigned int y, bool b) {
		unsigned char* cell_ptr = cells + (y * w) + x;

		int xL, xR, yA, yB;
		if (x == 0) { xL = w - 1; }
		else { xL = -1; }

		if (x == w - 1 ) { xR = -(w - 1); }
		else { xR = 1; }

		if (y == 0) { yA = length - w; }
		else { yA = -w; }

		if (y == h - 1) { yB = -(length - w); }
		else { yB = w; }

		int add = 0x02;
		if (b) {
			*(cell_ptr) |= 0x01; // set bit 1 to true
		} else {
			*(cell_ptr) &= ~0x01; // set bit 1 to false
			add *= -1;
		}
		*(cell_ptr + yA + xL) += add;
		*(cell_ptr + yA) += add;
		*(cell_ptr + yA + xR) += add;
		*(cell_ptr + xL) += add;
		*(cell_ptr + xR) += add;
		*(cell_ptr + yB + xL) += add;
		*(cell_ptr + yB) += add;
		*(cell_ptr + yB + xR) += add;
	}

	void CellMap::SetCell(unsigned int i, bool b) {
		SetCell(i % w, floor(i / h), b);
	}

	void CellMap::Tick() {
		unsigned int x, y, liveNeighbours;
		unsigned char* cell_ptr;

		memcpy(cellsBuffer, cells, length);

		cell_ptr = cellsBuffer;

		// Do stuff
		for (int i = 0; i < length; i++) {
			//if (i % w == 0) { out += "\n"; } // Add a line break if we're on the edge

			if (*cell_ptr == 0) { cell_ptr++; continue; } // Skip cell

			liveNeighbours = *cell_ptr >> 1;
			if (*cell_ptr & 0x01) {
				if (liveNeighbours != 2 && liveNeighbours != 3) { SetCell(i, false); }
			} else {
				if (liveNeighbours == 3) { SetCell(i, true); }
			}

			cell_ptr++;
		}
	}
}