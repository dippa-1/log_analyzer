#include <iostream>
#include <stdio.h>
#include <vector>

#define MAPSIZE 8000

namespace dh{
	template <typename T>
	struct Vector {
		T x;
		T y;
		T z;
	};
	void analyzePositions(void)
	{
		FILE* fp = nullptr;
		fopen_s(&fp, "00_t.dat", "rb");
		if (fp == nullptr) return;

		std::vector<dh::Vector<short> > positions;
		dh::Vector<short> pos;
		do {
			if (std::fread((void*)& pos, sizeof(pos), 1, fp) == 0U) break;
			positions.push_back(pos);
			std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
		} while (pos.x != EOF);

		// divide map into 100x100 rectangles
		constexpr int rectSize = 80;
		constexpr int nRects = MAPSIZE/rectSize;
		size_t* division[nRects];
		for (size_t i = 0U; i < nRects; ++i) division[i] = new size_t[nRects];

		for (size_t i = 0U; i < positions.size(); ++i) {
			const int x = ((positions[i].x + MAPSIZE/2) - (positions[i].x + MAPSIZE/2) % rectSize) / rectSize;
			const int y = ((positions[i].y + MAPSIZE/2) - (positions[i].y + MAPSIZE/2) % rectSize) / rectSize;
			++division[x][y];
		}
		for (size_t i = 0U; i < nRects; ++i) delete[] division[i];

		fclose(fp);
	}
} // namespace dh


int main(void)
{
	dh::analyzePositions();

	return 0;
}