using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PauseScript : MonoBehaviour
{
    public Canvas pauseCanvas;
    public PlayerController player;
    private bool paused = false;
    // Update is called once per frame
    void Update()
    {
        if (!player.dead)
        {
            if (Input.GetKeyDown(KeyCode.Escape) && !paused)
            {
                paused = true;
                Time.timeScale = 0.0f;
                pauseCanvas.enabled = true;
            }
            else if (Input.GetKeyDown(KeyCode.Escape) && paused)
            {
                paused = false;
                Time.timeScale = 1.0f;
                pauseCanvas.enabled = false;
            }
        } 
    }
}