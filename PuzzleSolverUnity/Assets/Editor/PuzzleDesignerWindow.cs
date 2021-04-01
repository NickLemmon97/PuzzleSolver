using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class PuzzleDesignerWindow : EditorWindow
{

    public PuzzleLayout CurrentLayout;

    [MenuItem("Puzzle/Puzzle Designer")]
    static void Init()
    {
        PuzzleDesignerWindow window = (PuzzleDesignerWindow)EditorWindow.GetWindow(typeof(PuzzleDesignerWindow));
        window.Show();
    }

    private void OnEnable()
    {
        if (EditorPrefs.HasKey("ObjectPath"))
        {
            string objectPath = EditorPrefs.GetString("ObjectPath");
            CurrentLayout = AssetDatabase.LoadAssetAtPath(objectPath, typeof(PuzzleLayout)) as PuzzleLayout;
        }
    }

    private void OnGUI()
    {
        DisplayHeader();

        if (CurrentLayout == null)
        {
            return;
        }

        DisplayLayout();

        if (GUI.changed)
        {
            EditorUtility.SetDirty(CurrentLayout);
        }
    }

    void DisplayHeader()
    {
        EditorGUILayout.BeginHorizontal();
        {
            if (GUILayout.Button("Open Puzzle Layout", GUILayout.ExpandWidth(false)))
            {
                OpenPuzzleLayout();
            }

            if (GUILayout.Button("New Puzzle Layout", GUILayout.ExpandWidth(false)))
            {
                CreatePuzzleLayout();
            }
        }
        EditorGUILayout.EndHorizontal();
    }

    void DisplayLayout()
    {
        GUILayout.Label("Layout:");

        for (int pieces = 0; pieces < 64; pieces += 16)
        {
            //Top Pieces
            EditorGUILayout.BeginHorizontal();
            {
                CreatePieceLocationPrespacing(pieces, true);
                CreatePieceLocationPrespacing(pieces + 4, true);
                CreatePieceLocationPrespacing(pieces + 8, true);
                CreatePieceLocationPrespacing(pieces + 12, true);
            }
            EditorGUILayout.EndHorizontal();

            //Left-Right
            EditorGUILayout.BeginHorizontal();
            {
                CreatePieceLocation(pieces + 3);
                CreatePieceLocation(pieces + 1, true);

                CreatePieceLocation(pieces + 7);
                CreatePieceLocation(pieces + 5, true);

                CreatePieceLocation(pieces + 11);
                CreatePieceLocation(pieces + 9, true);

                CreatePieceLocation(pieces + 15);
                CreatePieceLocation(pieces + 13, true);
            }
            EditorGUILayout.EndHorizontal();

            //Bottom pieces
            EditorGUILayout.BeginHorizontal();
            {
                CreatePieceLocationPrespacing(pieces + 2, true);
                CreatePieceLocationPrespacing(pieces + 6, true);
                CreatePieceLocationPrespacing(pieces + 10, true);
                CreatePieceLocationPrespacing(pieces + 14, true);
            }
            EditorGUILayout.EndHorizontal();

            //Ending space
            EditorGUILayout.BeginHorizontal();
            EditorGUILayout.Space();
            EditorGUILayout.EndHorizontal();
        }
    }

    void OpenPuzzleLayout()
    {
        string absPath = EditorUtility.OpenFilePanel("Select Puzzle Layout", "", "");
        if (absPath.StartsWith(Application.dataPath))
        {
            string relPath = absPath.Substring(Application.dataPath.Length - "Assets".Length);
            CurrentLayout = AssetDatabase.LoadAssetAtPath(relPath, typeof(PuzzleLayout)) as PuzzleLayout;
            if (CurrentLayout)
            {
                EditorPrefs.SetString("ObjectPath", relPath);
            }
        }
    }

    void CreatePuzzleLayout()
    {
        //TODO: Implement
    }

    void CreatePieceLocation(int index, bool withspace = false, int spacing = 1)
    {
        CurrentLayout.LayoutData[index] = EditorGUILayout.IntField(CurrentLayout.LayoutData[index]);

        if (withspace)
        {
            EditorGUILayout.Space(spacing);
        }
    }

    void CreatePieceLocationPrespacing(int index, bool withspace = false, int postspace = 1, int prespace = 10)
    {
        EditorGUILayout.Space(prespace);

        CreatePieceLocation(index, withspace, postspace);
    }

}
