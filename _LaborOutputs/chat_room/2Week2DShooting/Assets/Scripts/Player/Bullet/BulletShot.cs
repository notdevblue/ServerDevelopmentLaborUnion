using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletShot : MonoBehaviour
{
    public float damage = 5;
    public float coolTime = 1;
    
    public float hp = 10;

    public float time = 0;

    public Transform poolTransform;
    public List<Bullet> bullets;
    public int bulletCount = 0;
    public GameObject bulletPrefab;

    void Update()
    {
        time += Time.deltaTime;
        if (Input.GetMouseButton(0))
        {
            if (coolTime <= time)
            {
                Bullet bulletData = null;
                if (bullets.Count > bulletCount)
                {
                    for (int i = 0; i < bullets.Count; i++)
                    {
                        if (!bullets[i].isTriggered)
                        {
                            bullets[i].gameObject.SetActive(true);
                            bulletData = bullets[i];
                        }
                    }
                }
                else
                {
                    GameObject bullet = Instantiate(bulletPrefab, transform.position, Quaternion.identity, poolTransform);
                    bulletData = bullet.GetComponent<Bullet>();
                    bullets.Add(bulletData);
                }
                bulletData.SetBullet(damage, Camera.main.ScreenToWorldPoint(Input.mousePosition), "PLAYER");
                bulletData.shot = this;
                bulletCount++;
                time = 0;
            }
        }
    }
}
