using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OpenLeaderboardButton : MonoBehaviour
{
    public Canvas leaderboard;
    public LeaderboardManager manager;
    public void OnClick()
    {
        manager.GetLeaderboard();
        leaderboard.enabled = true;
    }
}
