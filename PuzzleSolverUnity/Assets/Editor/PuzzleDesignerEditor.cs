using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEditor.UI;
using UnityEngine;

[CustomEditor(typeof(PuzzleLayout))]
public class PuzzleDesignerEditor : Editor
{
    SerializedProperty PuzzlePieceData;
    public void OnEnable()
    {
        PuzzlePieceData = serializedObject.FindProperty("LayoutData");
    }

    public override void OnInspectorGUI()
    {
        serializedObject.Update();
    
        PuzzleLayout pLayout = (PuzzleLayout)target;
    
        if(pLayout != null)
        {
            for(int i = 0; i < 16; i++)
            {
                string PieceLabel = "Piece ";
                PieceLabel += (i + 1).ToString();

                EditorGUILayout.LabelField(PieceLabel);

                EditorGUI.indentLevel++;

                for (int j = 0; j < 4; j++)
                {
                    string SideLabel = "Side: ";
                    switch (j)
                    {
                        case 0:
                            SideLabel += "top:";
                            break;
                        case 1:
                            SideLabel += "right: ";
                            break;
                        case 2:
                            SideLabel += "bottom: ";
                            break;
                        case 3:
                            SideLabel += "left: ";
                            break;
                    }//end switch

                    EditorGUILayout.LabelField(SideLabel);
                    pLayout.LayoutData[i*4+j] = EditorGUILayout.IntField(pLayout.LayoutData[i*4+j]);
                }//for j

                EditorGUI.indentLevel--;
            }//for i

        }//end if
        if(GUI.changed)
        {
            EditorUtility.SetDirty(target);
        }
    }//end function
}
