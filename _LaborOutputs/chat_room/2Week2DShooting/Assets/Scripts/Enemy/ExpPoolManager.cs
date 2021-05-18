using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExpPoolManager : MonoBehaviour
{
    public static ExpPoolManager instance;

    public GameObject expObjPrefab;
    public Queue<GameObject> expQueue = new Queue<GameObject>();

    public float xPos;
    public float yPos;
    public float max = 10f;
    private Vector3 randomVector;

    private void Awake()
    {
        instance = this;

        for (int i = 0; i < 10; i++)
        {
            GameObject obj = Instantiate(expObjPrefab, this.gameObject.transform);
            expQueue.Enqueue(obj);
            obj.SetActive(false);
        }
    }

    private void Start()
    {
        StartCoroutine(ExpObjSpawn());
    }


    public void InsertQueue(GameObject obj)
    {
        expQueue.Enqueue(obj);
        obj.SetActive(false);
    }
    public GameObject GetQueue()
    {
        GameObject obj = expQueue.Dequeue();
        obj.SetActive(true);
        return obj;
    }

    IEnumerator ExpObjSpawn()
    {
        while (true)
        {
            if(expQueue.Count != 0)
            {
                xPos = Random.Range(-max, max);
                yPos = Random.Range(-max, max);

                randomVector = new Vector3(xPos, yPos, 0);
                GameObject obj = GetQueue();
                obj.transform.position = gameObject.transform.position + randomVector;
            }
            yield return new WaitForSeconds(1f);
        }
    }
}
