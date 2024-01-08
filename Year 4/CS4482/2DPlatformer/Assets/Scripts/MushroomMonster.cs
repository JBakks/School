using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MushroomMonster : MonoBehaviour
{
    public float moveSpeed = 5.0f;
    public float moveRange = 5.0f;
    public SpriteRenderer spriteRenderer;
    public Animator animator;

    private PlayerController player;

    private bool movingRight = true;
    private bool shouldUpdate = true;
    private float originalX;
    private float originalY;
    private float originalZ;

    private void OnEnable()
    {
        EventManager.OnRespawn.AddListener(Respawn);
    }

    private void OnDisable()
    {
        EventManager.OnRespawn.RemoveListener(Respawn);
    }
    void Start()
    {
        GameObject playerObject = GameObject.Find("Player");
        player = playerObject.GetComponent<PlayerController>();

        originalX = transform.position.x;
        originalY = transform.position.y;
        originalZ = transform.position.z;
    }

    // Update is called once per frame
    void Update()
    {
        if (shouldUpdate)
        {
            // Movement
            if (movingRight)
            {
                transform.Translate(Vector2.right * moveSpeed * Time.deltaTime);
            }
            else
            {
                transform.Translate(Vector2.left * moveSpeed * Time.deltaTime);
            }

            if (transform.position.x >= originalX + moveRange)
            {
                spriteRenderer.flipX = true;
                movingRight = false;
            }
            if (transform.position.x <= originalX - moveRange)
            {
                spriteRenderer.flipX = false;
                movingRight = true;
            }
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Player") && player.attacking || collision.gameObject.CompareTag("Projectile"))
        {
            Die();
        }
        else if(collision.gameObject.CompareTag("Player"))
        {
            animator.SetTrigger("Attack");
        }
    }

    private void Die()
    {
        Debug.Log("IM DEAD");
        animator.SetTrigger("Death");
        shouldUpdate = false;
        gameObject.layer = LayerMask.NameToLayer("Ignore");
    }

    public void Respawn()
    {
        shouldUpdate = true;
        transform.position = new Vector3(originalX, originalY, originalZ);
        gameObject.layer = LayerMask.NameToLayer("Default");
        animator.Play("Run");
    }
}
