#pragma once
#pragma warning(disable:4146)
#include <vector>
#include <string>
#include "include/SDL.h"

namespace Life {
	class CellMap {
	public:
		unsigned int length;
		unsigned char* cells;
		CellMap(unsigned int width, unsigned int height);
		~CellMap();

		void SetCell(unsigned int x, unsigned int y, bool b);
		void SetCell(unsigned int i, bool b);
		void Tick();
	private:
		SDL_Surface* surface;
		unsigned char *cellsBuffer;
		unsigned int w, h;
	};
}

