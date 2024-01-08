using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class EventManager : MonoBehaviour
{
    public static UnityEvent OnRespawn = new UnityEvent();

    public static void TriggerRespawn()
    {
        OnRespawn.Invoke();
    }
}
