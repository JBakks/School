using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EyeMonster : MonoBehaviour
{
    private GameObject player;
    private PlayerController playerController;
    
    public GameObject projectilePrefab;
    public SpriteRenderer spriteRenderer;
    public Animator animator;
    public BoxCollider2D boxCollider;
    public Rigidbody2D monsterRb;

    public float moveSpeed = 5.0f;
    public float moveRange = 5.0f;
    public float projectileSpeed = 2.0f;
    public float proximityDistance = 5.0f;
    public float shootingInterval = 3f;
    
    private bool movingRight = true;
    private bool shouldUpdate = true;
    private float originalX;
    private float originalY;
    private float originalZ;
    private float timeSinceLastShot = 0f;

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
        player = GameObject.Find("Player");
        playerController = player.GetComponent<PlayerController>();
        originalX = transform.position.x;
        originalY = transform.position.y; 
        originalZ = transform.position.z;   
    }

    void Update()
    {
        if (shouldUpdate) {
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

            // Attack
            timeSinceLastShot += Time.deltaTime;

            if (timeSinceLastShot >= shootingInterval && IsPlayerInRange() && !playerController.dead)
            {
                ShootProjectile();
                timeSinceLastShot = 0f;
            }
        }
    }

    private void ShootProjectile()
    {
        GameObject newProjectile = Instantiate(projectilePrefab, transform.position, Quaternion.identity);

        Vector3 directionToPlayer = (player.transform.position - transform.position).normalized;

        Rigidbody2D rb = newProjectile.GetComponent<Rigidbody2D>();
        if(rb != null)
        {
            rb.velocity = directionToPlayer * projectileSpeed;
            rb.gravityScale = 0.0f;
        }
    }

    private bool IsPlayerInRange()
    {
        float distanceToPlayer = Vector3.Distance(transform.position, player.transform.position);
        return distanceToPlayer <= proximityDistance;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.CompareTag("Player") && playerController.attacking)
        {
            Die();
        }
        if (collision.gameObject.CompareTag("Projectile"))
        {
            Die();
        }
    }

    private void Die()
    {
        animator.SetTrigger("Death");
        shouldUpdate = false;
        monsterRb.gravityScale = 9;
        gameObject.layer = LayerMask.NameToLayer("Ignore");
        boxCollider.size = new Vector2(0.42f, 0.46f);
        //Destroy(gameObject);
    }

    public void Respawn()
    {
        shouldUpdate = true;
        transform.position = new Vector3(originalX, originalY, originalZ);
        boxCollider.size = new Vector2(0.42f, 0.32f);
        gameObject.layer = LayerMask.NameToLayer("EyeMonster");
        monsterRb.gravityScale = 0;
        animator.Play("Idle");
    }
}
