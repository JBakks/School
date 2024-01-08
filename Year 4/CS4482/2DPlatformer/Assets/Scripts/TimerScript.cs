using System;
using System.Collections.Generic;
using System.IO;
using TMPro;
using UnityEngine;
using UnityEngine.UI;

public class TimerScript : MonoBehaviour
{
    public float timeSinceStart;
    public bool timerOn = false;
    public TextMeshProUGUI timerTxt;


    private void OnEnable()
    {
        EventManager.OnRespawn.AddListener(Restart);
    }

    private void OnDisable()
    {
        EventManager.OnRespawn.RemoveListener(Restart);
    }

    void Start()
    {
        timerOn = true;
    }

    void Update()
    {
        if (timerOn)
        {
            timeSinceStart += Time.deltaTime;
            updateTimer(timeSinceStart);
        }
    }

    void updateTimer(float currentTime)
    {
        float seconds = Mathf.FloorToInt(currentTime % 60);
        timerTxt.text = string.Format("{000}", seconds);
    }

    void Restart()
    {
        timeSinceStart = 0;
    }
}
