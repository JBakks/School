using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RespawnButton : MonoBehaviour
{
    public Canvas gameOverCanvas;
    public void onClick()
    {
        gameOverCanvas.enabled = false;
        EventManager.TriggerRespawn();
    }

}