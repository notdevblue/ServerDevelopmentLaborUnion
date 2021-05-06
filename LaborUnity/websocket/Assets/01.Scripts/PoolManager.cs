using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PoolManager : MonoBehaviour
{
    public static PoolManager instance;

    private Queue<AudioSource> pool  = new Queue<AudioSource>();

    public GameObject audioPrefab;

    private void Awake()
    {
        instance = this;
        for(int i = 0; i < 10; i++)
        {
            GameObject obj = Instantiate(audioPrefab, transform);
            AudioSource a = obj.GetComponent<AudioSource>();
            pool.Enqueue(a);
            obj.SetActive(false);
        }
    }

    public AudioSource GetOrCreate()
    {
        AudioSource a = pool.Peek();
        if (a.gameObject.activeSelf)
        {
            GameObject obj = Instantiate(audioPrefab, transform);
            a = obj.GetComponent<AudioSource>();
            pool.Enqueue(a);
        }
        else {
            a = pool.Dequeue();
            a.gameObject.SetActive(true);
            pool.Enqueue(a);
        }
        
        return a;
    }
}
