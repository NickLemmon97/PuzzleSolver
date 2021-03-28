using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class PuzzleSolver : IDisposable
{
    public PuzzleSolver()
    {
        Impl = PuzzleSolver_Create();
    }

    public void GenerateDefaultLayout()
    {
        PuzzleSolver_GenerateDefaultLayout(Impl);
    }

    public void SolvePuzzle()
    {
        PuzzleSolver_SolvePuzzle(Impl);
    }

    public int GetNumSolutions()
    {
        return PuzzleSolver_GetNumSolutions(Impl);
    }


    IntPtr Impl;


    ~PuzzleSolver()
    {
        Cleanup();
    }

    public void Dispose()
    {
        Cleanup();
    }

    public void Cleanup()
    {
        if (Impl != IntPtr.Zero)
        {
            PuzzleSolver_Destroy(Impl);
            Impl = IntPtr.Zero;
        }
    }

    [DllImport("PuzzleSolverAPI")]
    private static extern IntPtr PuzzleSolver_Create();

    [DllImport("PuzzleSolverAPI")]
    private static extern void PuzzleSolver_Destroy(IntPtr solverPtr);

    [DllImport("PuzzleSolverAPI")]
    private static extern void PuzzleSolver_GenerateDefaultLayout(IntPtr solverPtr);

    [DllImport("PuzzleSolverAPI")]
    private static extern void PuzzleSolver_SolvePuzzle(IntPtr solverPtr);

    [DllImport("PuzzleSolverAPI")]
    private static extern int PuzzleSolver_GetNumSolutions(IntPtr solverPtr);

}
