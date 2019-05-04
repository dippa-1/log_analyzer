#include "OutputWindow.hpp"
#include "Evaluator.hpp"
#include "AssetManager.hpp"

#define MAPSIZE 8000

AssetManager assets;
dh::Evaluator Eval;

int main(void)
{
	//dh::analyzePositions();
	dh::OutputWindow window;
	Eval.window = &(window.window);
	window.Init("de_cache");
	Eval.evalMap("de_cache", window.info);
	window.Run();

	return 0;
}