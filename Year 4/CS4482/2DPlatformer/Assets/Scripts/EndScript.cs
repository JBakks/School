using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
public class EndScript : MonoBehaviour { 

    public Canvas leaderboard;
    public TMP_InputField inputField;
    private void OnCollisionEnter2D(Collision2D collision)
    {
        inputField.readOnly = false;
        leaderboard.enabled = true;
        Time.timeScale = 0;
    }
}
