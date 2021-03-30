#include "PuzzleSolverAPI.h"
#include "PuzzleSolver.h"

PLUGIN_API void* PuzzleSolver_Create()
{
	return new PuzzleSolver();
}

PLUGIN_API void  PuzzleSolver_Destroy(void* solverPtr)
{
	PuzzleSolver* solver = static_cast<PuzzleSolver*>(solverPtr);

	if (solver != nullptr)
	{
		delete solver;
		solver = nullptr;
	}
}

PLUGIN_API void  PuzzleSolver_GenerateDefaultLayout(void* solverPtr)
{
	PuzzleSolver* solver = static_cast<PuzzleSolver*>(solverPtr);

	solver->GenerateDefaultLayout();
}

PLUGIN_API void  PuzzleSolver_SolvePuzzle(void* solverPtr)
{
	PuzzleSolver* solver = static_cast<PuzzleSolver*>(solverPtr);

	solver->SolvePuzzle();
}

PLUGIN_API void PuzzleSolver_GenerateLayoutFromIntArr(void* solverPtr, int* dataArr)
{
	PuzzleSolver* solver = static_cast<PuzzleSolver*>(solverPtr);

	solver->GenerateLayoutFromIntArr(dataArr);
}

PLUGIN_API int   PuzzleSolver_GetNumSolutions(void* solverPtr)
{
	PuzzleSolver* solver = static_cast<PuzzleSolver*>(solverPtr);

	return solver->GetNumSolutions();
}

PLUGIN_API void PuzzleSolver_GetUnityPiece(void* solverPtr, int index, int* arr)
{
	PuzzleSolver* solver = static_cast<PuzzleSolver*>(solverPtr);

	Piece piece = solver->GetPieceAtIndex(index);

	for (int i = 0; i < 4; i++)
	{
		int val = 0;
		switch (piece._Sides[i]._Type)
		{
		case ShapeType::Cross:
			val = 0;
			break;

		case ShapeType::Circle:
			val = 2;
			break;

		case ShapeType::InArrow:
			val = 4;
			break;

		case ShapeType::OutArrow:
			val = 6;
			break;
		}

		if (piece._Sides[i]._Inward)
		{
			val++;
		}

		arr[i] = val;
	}

}

PLUGIN_API void PuzzleSolver_GetUnitySolution(void* solverPtr, int index, int* order, int* rotations)
{
	PuzzleSolver* solver = static_cast<PuzzleSolver*>(solverPtr);

	Piece* solution = solver->GetSolutionAtIndex(index);

	for (int i = 0; i < 16; i++)
	{
		order[i] = solution[i]._Index - 1;
		rotations[i] = solution[i]._Rotation;
	}
}
