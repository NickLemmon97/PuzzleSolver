#include <iostream>
#include <memory>
#include "PuzzleSolver.h"

int main()
{
	std::unique_ptr<PuzzleSolver> solver = std::make_unique<PuzzleSolver>();

	solver->GenerateDefaultLayout();
	solver->SolvePuzzle();
	
	std::cout << solver->GetNumSolutions() << std::endl;

	std::cin.get();
	return 0;
}