using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ContinueButton : MonoBehaviour
{
    public Canvas pauseCanvas;
    public void onClick()
    {
        Time.timeScale = 1.0f;
        pauseCanvas.enabled = false;
    }
}
