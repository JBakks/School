using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StartButton : MonoBehaviour
{
    public Canvas startCanvas;
    void Start()
    {
        Time.timeScale = 0.0f;
    }

    public void StartGame()
    {
        Time.timeScale = 1.0f;
        startCanvas.enabled = false;
    }
}
