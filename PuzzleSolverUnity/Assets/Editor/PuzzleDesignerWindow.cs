using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class PuzzleDesignerWindow : EditorWindow
{
    [MenuItem("Puzzle/Puzzle Designer")]
    static void Init()
    {
        PuzzleDesignerWindow window = (PuzzleDesignerWindow)EditorWindow.GetWindow(typeof(PuzzleDesignerWindow));
        window.Show();
    }

    private void OnGUI()
    {
        GUILayout.Label("Demo");
    }
}
