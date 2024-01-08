using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowPlayer : MonoBehaviour
{
    public Transform player;
    public float smoothSpeed = 0.05f;
    public Vector3 offset;

    public float fixedYPos = 1.12f;

    // Update is called once per frame
    void FixedUpdate()
    {
        Vector3 currentpos = transform.position;

        float desiredXPos = player.position.x;
        float desiredYPos = fixedYPos;

        Vector3 desiredPos = new Vector3(desiredXPos, desiredYPos, currentpos.z);

        transform.position = Vector3.Lerp(currentpos, desiredPos, smoothSpeed);
        
    }
}
