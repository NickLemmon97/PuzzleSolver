using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[CreateAssetMenu(fileName = "New Layout", menuName = "Puzzle/Create New Puzzle Layout")]
public class PuzzleLayout : ScriptableObject
{
    public int[] LayoutData = new int[64];
}
