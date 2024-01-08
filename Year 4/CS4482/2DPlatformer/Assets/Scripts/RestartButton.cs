using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class RestartButton : MonoBehaviour
{
    public Canvas leaderboardCanvas;
    public TMP_InputField inputField;
    public void onClick()
    {
        leaderboardCanvas.enabled = false;
        EventManager.TriggerRespawn();
        Time.timeScale = 1;
        inputField.readOnly = true;
        inputField.text = "";
    }
}
