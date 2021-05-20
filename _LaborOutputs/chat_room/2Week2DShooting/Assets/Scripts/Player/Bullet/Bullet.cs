using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    public BulletShot shot;
    private float damage = 5;
    private Vector2 destination;
    private string sTag;
    public bool isTriggered;

    public float speed = 5;

    private void Awake()
    {
        isTriggered = false;
    }

    private void Update()
    {
        if (isTriggered)
        {
            Vector2 nyan = (Vector2)transform.position;
            transform.position = Vector2.MoveTowards(transform.position, destination, Time.deltaTime * speed);
            destination += (Vector2)transform.position - nyan;
        }
    }

    void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.CompareTag("ENEMY"))
        {

        }
        if (other.gameObject.CompareTag("WALL"))
        {

        }
        isTriggered = false;
        gameObject.SetActive(false);
        shot.bulletCount--;
    }

    public void SetBullet(float damage, Vector2 destination, string sTag)
    {
        this.damage = damage;
        this.destination = destination;
        this.sTag = sTag;
        isTriggered = true;
    }
}
