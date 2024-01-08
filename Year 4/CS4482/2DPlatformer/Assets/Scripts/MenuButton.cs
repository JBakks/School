using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuButton : MonoBehaviour
{
    public Canvas startCanvas;
    public Canvas menuCanvas;
    public void onClick()
    {
        Time.timeScale = 0.0f;
        startCanvas.enabled = true;
        menuCanvas.enabled = false;

    }
}
