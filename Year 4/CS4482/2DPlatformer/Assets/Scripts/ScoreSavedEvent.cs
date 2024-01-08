using UnityEngine.Events;

public class ScoreSavedEvent : UnityEvent<float, string> { }

public static class ScoreEventManager
{
    public static ScoreSavedEvent OnScoreSaved = new ScoreSavedEvent();
}
