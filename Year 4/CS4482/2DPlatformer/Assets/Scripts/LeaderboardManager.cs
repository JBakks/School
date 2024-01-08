using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
using Dan.Main;

public class LeaderboardManager : MonoBehaviour
{
    [SerializeField]
    private List<TextMeshProUGUI> names;
    [SerializeField]
    private List<TextMeshProUGUI> scores;

    private string publicLeaderboardKey = "3b0f92fa8072f6206939bb875c6f640c38eff7a0f55a333e5986ed090399e5ba";

    private void Start()
    {
        GetLeaderboard();
    }
    public void GetLeaderboard()
    {
        LeaderboardCreator.GetLeaderboard(publicLeaderboardKey, ((msg) =>
        {
            int loopLength = (msg.Length < names.Count) ? msg.Length : names.Count;
            for (int i = 0; i < loopLength; ++i)
            {
                names[i].text = msg[i].Username;
                scores[i].text = msg[i].Score.ToString();
            }
        }));
    }

    public void SetLeaderboardEntry(string username, int score)
    {
        LeaderboardCreator.ResetPlayer();
        if (username.Length >= 3)
        {
            PlayerPrefs.DeleteAll();
            LeaderboardCreator.UploadNewEntry(publicLeaderboardKey, username, score, ((msg) =>
            {
                Debug.Log("YES");
                GetLeaderboard();
            }));
        }
    }
}