using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class Solver : MonoBehaviour
{
    public GameObject ButtonPrefab;
    public GameObject PiecePrefab;

    public GameObject canvas;

    public Sprite[] PuzzleShapes;
    public Vector3[] Locations;
    public PuzzlePiece[] PuzzlePieces;

    public int Solutions = 20;
    public int ButtonOffsetX = 400;
    public int ButtonOffsetY = 200;

    public float PieceStartingX = -8.0f;
    public float PieceStartingY = 3.0f;
    public float PieceSpacing = 2.0f;

    public bool bUsePuzzleData = false;
    public PuzzleLayout PuzzleData;

    void Start()
    {
        m_PuzzleSolver = new PuzzleSolver();

        PuzzlePieces = new PuzzlePiece[16];
        Locations = new Vector3[16];
        CreateLocations();

        if (bUsePuzzleData == true && PuzzleData != null)
        {
            m_PuzzleSolver.GenerateLayoutFromIntArr(PuzzleData.LayoutData);
        }
        else
        {
            m_PuzzleSolver.GenerateDefaultLayout();
        }

        CreatePieces();
        
        m_PuzzleSolver.SolvePuzzle();

        Solutions = m_PuzzleSolver.GetNumSolutions();
        Debug.Log("Solutions: " + Solutions.ToString());

        CreateButton();
    }


    public void DisplaySolution(int solutionNum)
    {
        Debug.Log("Button pressed: " + solutionNum.ToString());

        int[] Order = new int[16];
        int[] Rotations = new int[16];

        m_PuzzleSolver.GetUnitySolution(solutionNum, Order, Rotations);

        for(int i = 0; i < 16; i++)
        {
            PuzzlePieces[Order[i]].transform.position = Locations[i];
            PuzzlePieces[Order[i]].SetCounterClockwiseRotation(Rotations[i]);
        }
    }

    private void CreateLocations()
    {
        for(int y = 0; y < 4; y++)
        {
            for(int x = 0; x < 4; x++)
            {
                Locations[(y * 4) + x] = new Vector3(PieceStartingX + (x * PieceSpacing), PieceStartingY - (y * PieceSpacing));
            }
        }
    }

    private void CreatePieces()
    {
        int[] PieceValues = new int[6];

        for(int i = 0; i < 16; i++)
        {
            GameObject piece = Instantiate(PiecePrefab);
            piece.transform.position = Locations[i];

            PuzzlePiece puzzlePiece = piece.GetComponent<PuzzlePiece>();
            puzzlePiece.SetPieceColor(new Color(Random.Range(0.2f,1.0f), 
                                                Random.Range(0.3f, 1.0f),
                                                Random.Range(0.2f, 1.0f)));

            m_PuzzleSolver.GetUnityPiece(i, PieceValues);

            puzzlePiece.SetTopSprite(PuzzleShapes[PieceValues[0]]);
            puzzlePiece.SetRightSprite(PuzzleShapes[PieceValues[1]]);
            puzzlePiece.SetBottomSprite(PuzzleShapes[PieceValues[2]]);
            puzzlePiece.SetLeftSprite(PuzzleShapes[PieceValues[3]]);

            PuzzlePieces[i] = puzzlePiece;
        }
    }

    private void CreateButton()
    {
        int RowsCount = (Solutions - 1) / 10;

        for (int i = 0; i < Solutions; i++)
        {
            GameObject newButton = Instantiate<GameObject>(ButtonPrefab);

            //Set position before placing inside the Canvas
            int InitialXPos = ButtonOffsetX - (RowsCount * 45);
            int InitialYPos = ButtonOffsetY;

            int XOffset = 45 * (i / 10);
            int YOffset = 45 * (i % 10);

            int XPos = InitialXPos + XOffset;
            int YPos = InitialYPos - YOffset;

            newButton.transform.position = new Vector3(XPos, YPos);
            newButton.transform.SetParent(canvas.transform, false);

            //Setup the variables
            SolutionButton solutionButton = newButton.GetComponent<SolutionButton>();
            solutionButton.SolutionIndex = i;
            solutionButton.solver = this;
        }
    }


    PuzzleSolver m_PuzzleSolver;
}
