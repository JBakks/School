using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackButton : MonoBehaviour
{
    public Canvas leaderboard;
    public void OnClick()
    {
        leaderboard.enabled = false;
    }
}
