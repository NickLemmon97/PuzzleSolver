using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEditor.UI;
using UnityEngine;

[CustomEditor(typeof(PuzzleLayout))]
public class PuzzleDesignerEditor : Editor
{
    SerializedProperty[] Properties = new SerializedProperty[64];

    public void OnEnable()
    {
        
    }

    //public override void OnInspectorGUI()
    //{
    //    serializedObject.Update();
    //
    //    PuzzleLayout pLayout = (PuzzleLayout)target;
    //
    //    if(pLayout != null)
    //    {
    //        for(int i = 0; i < 64; i++)
    //        {
    //             string PieceLabel = "Piece ";
    //             PieceLabel += (i / 4).ToString();
    //             PieceLabel += " ";
    //
    //             switch (i % 4)
    //             {
    //                 case 0:
    //                     PieceLabel += "top:";
    //                     break;
    //                 case 1:
    //                     PieceLabel += "right: ";
    //                     break;
    //                 case 2:
    //                     PieceLabel += "bottom: ";
    //                     break;
    //                 case 3:
    //                     PieceLabel += "left: ";
    //                     break;
    //             }
    //
    //             GUILayout.BeginHorizontal();
    //             EditorGUILayout.LabelField(PieceLabel);
    //             EditorGUILayout.IntField(pLayout.LayoutData[i]);
    //             GUILayout.EndHorizontal();
    //        }
    //    }
    //}
}
