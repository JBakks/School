using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    public Animator animator;
    public SpriteRenderer spriteRenderer;
    public Rigidbody2D playerRigidbody2D;
    public Canvas gameOverCanvas;
    public GameObject projectilePrefab;
    public BoxCollider2D collider;
    public Transform respawnPoint;

    public float horizontalInput;
    public float speed = 12.0f;
    public float jumpForce = 4.0f;
    public float fallThreshold = -5.0f;
    public bool dead = false;
    public bool attacking = false;

    private bool isFlipped;

    private void OnEnable()
    {
        EventManager.OnRespawn.AddListener(Respawn);
    }

    private void OnDisable()
    {
        EventManager.OnRespawn.RemoveListener(Respawn);
    }
    void Update()
    {
        if (!dead)
        {
            horizontalInput = Input.GetAxis("Horizontal");
            if (horizontalInput != 0)
            {
                if (horizontalInput < 0)
                {
                    spriteRenderer.flipX = true;
                    isFlipped = true;
                }
                else
                {
                    spriteRenderer.flipX = false;
                    isFlipped = false;
                }
                animator.SetBool("running", true);
            }
            else
            {
                animator.SetBool("running", false);
            }

            bool isGrounded = IsGrounded();

            if (Input.GetKeyDown(KeyCode.W) && isGrounded)
            {
                playerRigidbody2D.AddForce(new Vector2(0f, jumpForce), ForceMode2D.Impulse);
                animator.SetTrigger("jump");

            }
            if (isGrounded)
            {
                animator.SetTrigger("onGround");
            }
            if (Input.GetKeyDown(KeyCode.J) & isGrounded)
            {
                animator.SetTrigger("attack1");
                StartCoroutine(waitShoot());
            }
            if (Input.GetKeyDown(KeyCode.K))
            {
                attacking = true;
                animator.SetTrigger("attack2");
                collider.size = new Vector2(1.09f, 0.5537372f);
                StartCoroutine(waitAttack());
            }


            if (playerRigidbody2D.velocity.y < -0.1)
            {
                // Player is falling, trigger the fall animation.
                animator.SetTrigger("fall");
            }


            transform.Translate(Vector3.right * horizontalInput * Time.deltaTime * speed);
        }
    }
    

    private bool IsGrounded()
    {
        float rayLength = 0.001f; // Adjust this value based on your character's size
        Vector2 rayOrigin = transform.position - new Vector3(0f, GetComponent<Collider2D>().bounds.extents.y);

        RaycastHit2D hit = Physics2D.Raycast(rayOrigin, Vector2.down, rayLength, LayerMask.GetMask("Ground"));

        return hit.collider != null;
    }

    void FireProjectile()
    {
        GameObject newProjectile = Instantiate(projectilePrefab, transform.position, Quaternion.identity);

        Rigidbody2D rb = newProjectile.GetComponent<Rigidbody2D>();

        if (rb != null)
        {
            if (isFlipped)
            {
                rb.transform.rotation = Quaternion.Euler(0.0f, 180.0f, 0.0f);
                rb.velocity = -transform.right * 30;
            }
            else
            {
                rb.transform.rotation = Quaternion.Euler(0.0f, 0.0f, 0.0f);
                rb.velocity = transform.right * 30;
            }
        }
    }
    IEnumerator waitShoot()
    {
        //Wait for 0.4 seconds
        yield return new WaitForSeconds(0.4f);
        FireProjectile();
    }

    IEnumerator waitAttack()
    {
        yield return new WaitForSeconds(0.5f);
        collider.size = new Vector2(0.2167934f, 0.511049f);
        attacking = false;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("EyeShot") || collision.gameObject.CompareTag("Lava"))
        {
            Die();
        }

        if (collision.gameObject.CompareTag("Monster") && !attacking){
            Die();
        }
    }

    private void Die()
    {
        dead = true;
        animator.SetTrigger("Death");
        gameOverCanvas.enabled = true;
        gameObject.layer = LayerMask.NameToLayer("Ignore");
    }

    private void Respawn()
    {
        gameObject.layer = LayerMask.NameToLayer("Player");
        dead = false;
        animator.Play("Idle");
        transform.position = respawnPoint.position;
    }
}

