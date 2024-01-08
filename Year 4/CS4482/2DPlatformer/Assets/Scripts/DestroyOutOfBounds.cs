using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyOutOfBounds : MonoBehaviour
{
    private float sideBound = 20;
    private Transform cameraTransform;

    // Update is called once per frame
    void Update()
    {
        cameraTransform = Camera.main.transform;
        if (transform.position.x > sideBound + cameraTransform.position.x)
        {
            Destroy(gameObject);
        }
        else if (transform.position.x < cameraTransform.position.x - sideBound)
        {
            Destroy(gameObject);
        }
    }
}
