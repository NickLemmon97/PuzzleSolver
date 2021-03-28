#include <iostream>
#include <memory>
#include "PuzzleSolver.h"

void PrintPieces(std::vector<Piece>& pieces);

int main()
{
	std::unique_ptr<PuzzleSolver> solver = std::make_unique<PuzzleSolver>();

	solver->GenerateDefaultLayout();
	solver->SolvePuzzle();
	
	std::cout << solver->GetNumSolutions() << std::endl;

	solver->SetDrawFunction(&PrintPieces);
	solver->DrawSolutions();


	std::cin.get();
	return 0;
}


void PrintPieces(std::vector<Piece>& pieces)
{
	std::cout << "Solution:\n";
	for (int i = 0; i < pieces.size(); i++)
	{
		std::cout << "Piece 1 has index " << pieces[i]._Index << " and is rotated counter clockwise " << pieces[i]._Rotation << " times\n";
	}
	std::cout << "\n\n";
}
