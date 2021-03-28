#pragma once
#include <vector>
#include "Piece.h"

class PuzzleSolver
{
public:
	PuzzleSolver();
	~PuzzleSolver();

	void GenerateDefaultLayout();
	void SolvePuzzle();


	int GetNumSolutions() { return _Solutions.size(); }

private:
	inline bool IsUniqueSetOf2(std::vector<Piece>& p1, std::vector<Piece>& p2)
	{
		return
			p1[0]._Index != p2[0]._Index &&
			p1[0]._Index != p2[1]._Index &&
			p1[1]._Index != p2[0]._Index &&
			p1[1]._Index != p2[1]._Index;
	}

private:
	BaseShape _Shapes[8];
	std::vector<Piece> _Pieces;
	std::vector<std::vector<Piece>> _Solutions;
};

