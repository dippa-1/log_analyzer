#include "Evaluator.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "dirent.h"
#include <Windows.h>
#include <filesystem>
#include "AssetManager.hpp"
#include <cmath>

dh::Evaluator::Evaluator()
{
	window = nullptr;
}
dh::Evaluator::~Evaluator()
{
}

void dh::Evaluator::evalMap(std::string map, std::vector<sf::Text>& info)
{
	FILE* fp = nullptr;
	std::string fname = "logs/" + map + "/";
	std::string fnameBounds = fname + "bounds.txt";

	// read bounds first
	fopen_s(&fp, fnameBounds.c_str(), "r");
	int xmin = 0, xmax = 0, ymin = 0, ymax = 0;
	if (fp != nullptr)
		fscanf_s(fp, "%d %d\n%d %d", &xmin, &xmax, &ymin, &ymax);
	std::cout << xmin << std::endl;
	std::cout << xmax << std::endl;
	std::cout << ymin << std::endl;
	std::cout << ymax << std::endl;
	if (fp != nullptr)
		fclose(fp);

	const unsigned int width = xmax - xmin;
	const unsigned int height = ymax - ymin;

	// get all files
	std::vector<std::string> filenames;
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir(fname.c_str())) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			std::string f(ent->d_name);
			//std::cout << f << std::endl;
			if (f.find("pos") == std::string::npos) continue;
			filenames.push_back(f);
		}
		closedir(dir);
	}
	else {
		/* could not open directory */
		perror("");
		return;
	}

	// divide map into 80x80 rectangles
	constexpr int rectSize = 80;
	const size_t nRectsX = width / rectSize;
	const size_t nRectsY = height / rectSize;
	size_t** division = new size_t * [nRectsX] {nullptr};
	for (size_t i = 0U; i < nRectsX; ++i) division[i] = new size_t[nRectsY]{ 0U };
	unsigned int max = 0U;
	// iterate through all log files
	for (size_t i = 0U; i < filenames.size(); ++i)
	{
		std::string fnameLog = fname + filenames[i];
		std::cout << fnameLog << std::endl;
		fopen_s(&fp, fnameLog.c_str(), "rb");
		if (fp == nullptr) return;

		dh::Vector<short> pos;
		do {
			if (std::fread((void*)& pos, sizeof(pos), 1, fp) == 0U) break;
			//std::cout << " >" << pos.x << "|" << pos.y << "< ";
			int x = ((pos.x + std::abs(xmin)) - (pos.x + std::abs(xmin)) % rectSize) / rectSize;
			int y = ((pos.y + std::abs(ymin)) - (pos.y + std::abs(ymin)) % rectSize) / rectSize;
			if (x >= nRectsX) x = nRectsX - 1;
			if (y >= nRectsY) y = nRectsY - 1;
			++division[x][y];
			if (division[x][y] > max) max = division[x][y];
		} while (pos.x != EOF && pos.y != EOF && pos.z != EOF);
		/*std::cout << std::endl;
		std::cout << "########################################" << std::endl;
		std::cout << std::endl;*/

		fclose(fp);
	}

	for (size_t x = 0U; x < nRectsX; ++x)
		for (size_t y = 0U; y < nRectsY; ++y) {
			size_t curr = division[x][y];
			int percent = (int)(100.0f * curr / max);
			if (percent == 0) continue;
			sf::Text txt;
			txt.setFont(assets.getFont("Font"));
			txt.setString(std::to_string(percent));
			float scalex = 0.75f * txt.getLocalBounds().width / (window->getSize().x / nRectsX);
			float scaley = 0.75f * txt.getLocalBounds().height / (window->getSize().y / nRectsY);
			//txt.scale(1.0f / scalex, 1.0f / scaley);
			if (scalex < scaley) txt.setCharacterSize((unsigned int)(txt.getCharacterSize()/3.0f * scalex));
			else txt.setCharacterSize((unsigned int)(txt.getCharacterSize()/3.0f * scaley));
			txt.setOrigin(txt.getLocalBounds().width / 2.0f, txt.getLocalBounds().height / 2.0f);
			txt.setPosition((float)x * window->getSize().x / nRectsX, (float)y * window->getSize().y / nRectsY);
			txt.setFillColor(sf::Color(0, 0, 0, 255));
			info.push_back(txt);
		}
	for (size_t x = 0U; x < nRectsX; ++x) delete[] division[x];
	delete[] division;
}