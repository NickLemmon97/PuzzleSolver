using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Solver : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        m_PuzzleSolver = new PuzzleSolver();
        m_PuzzleSolver.GenerateDefaultLayout();
        m_PuzzleSolver.SolvePuzzle();

        int Solutions = m_PuzzleSolver.GetNumSolutions();

        Debug.Log("Solutions: " + Solutions.ToString());
    }


    PuzzleSolver m_PuzzleSolver;
}
