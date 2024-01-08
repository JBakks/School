using UnityEngine;
using System.Reflection;

public class PlayerPrefsViewer : MonoBehaviour
{
    void Start()
    {
        // Use reflection to get the private keys field
        FieldInfo keysField = typeof(PlayerPrefs).GetField("keys", BindingFlags.NonPublic | BindingFlags.Static);

        // Get the keys array from the field
        string[] keys = (string[])keysField.GetValue(null);

        // Display all PlayerPrefs keys and values
        foreach (string key in keys)
        {
            Debug.Log($"{key}: {PlayerPrefs.GetString(key)}");
        }
    }
}
