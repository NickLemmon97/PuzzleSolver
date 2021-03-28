using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SolutionButton : MonoBehaviour
{
    public int SolutionIndex { get; set; }

    public Solver solver;

    Button button;

    void Start()
    {
        button = GetComponent<Button>();

        if(button != null)
        {
            button.onClick.AddListener(OnButtonClick);

            Text t = button.GetComponentInChildren<Text>();
            if(t != null)
            {
                t.text = (SolutionIndex + 1).ToString();
            }
        }
    }

    public void OnButtonClick()
    {
        solver.DisplaySolution(SolutionIndex);
    }

}
