#pragma once

#ifdef PUZZLESOLVER_EXPORTS
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#endif


extern "C"
{
	PLUGIN_API void* PuzzleSolver_Create();
	PLUGIN_API void  PuzzleSolver_Destroy(void* solverPtr);
	PLUGIN_API void  PuzzleSolver_GenerateDefaultLayout(void* solverPtr);
	PLUGIN_API void  PuzzleSolver_SolvePuzzle(void* solverPtr);

	PLUGIN_API int   PuzzleSolver_GetNumSolutions(void* solverPtr);

	PLUGIN_API void  PuzzleSolver_GetUnityPiece(void* solverPtr, int index, int* arr);
	PLUGIN_API void  PuzzleSolver_GetUnitySolution(void* solverPtr, int index, int* order, int* rotations);
}
