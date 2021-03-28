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
