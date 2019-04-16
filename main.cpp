#include <iostream>
#include <stdio.h>
#include <vector>

namespace dh{
	struct Vector {
		float x;
		float y;
		float z;
	};
	void analyzePositions(void)
	{
		FILE* fp = nullptr;
		fopen_s(&fp, "enemy_positions_log.dat", "rb");
		if (fp == nullptr) return;

		std::vector<dh::Vector> positions;
		dh::Vector pos;
		do
		{
			if (std::fread((void*)& pos, sizeof(pos), 1, fp) == 0U) break;
			positions.push_back(pos);
			std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
		} while (pos.x != EOF);

		// divide map into 50x50 rectangles
		size_t division[60][60] = { 0 };
		for (size_t i = 0U; i < positions.size(); ++i) {
			division[][]
		}

		fclose(fp);
	}
} // namespace dh


int main(void)
{
	dh::analyzePositions();

	return 0;
}