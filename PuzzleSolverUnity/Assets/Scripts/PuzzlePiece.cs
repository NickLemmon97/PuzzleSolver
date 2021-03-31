using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PuzzlePiece : MonoBehaviour
{

    public SpriteRenderer TopShape;
    public SpriteRenderer RightShape;
    public SpriteRenderer BottomShape;
    public SpriteRenderer LeftShape;

    // Start is called before the first frame update

    public void SetCounterClockwiseRotation(int rotation)
    {
        this.transform.rotation = Quaternion.Euler(0, 0, 0);
        Vector3 eulerRotation = new Vector3(0, 0, 90 * rotation);
        this.transform.rotation = Quaternion.Euler(eulerRotation);
    }

    public void SetPieceColor(Color col)
    {
        TopShape.color = col;
        RightShape.color = col;
        BottomShape.color = col;
        LeftShape.color = col;
    }

    public void SetTopSprite(Sprite Shape)
    {
        TopShape.sprite = Shape;
    }
    public void SetRightSprite(Sprite Shape)
    {
        RightShape.sprite = Shape;
    }
    public void SetBottomSprite(Sprite Shape)
    {
        BottomShape.sprite = Shape;
    }
    public void SetLeftSprite(Sprite Shape)
    {
        LeftShape.sprite = Shape;
    }

}
