using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerLevelup : MonoBehaviour
{
    #region 임시 변수
    public int level = 1;

    private float size = 1;

    public bool levelUP = true;

    #endregion


    void Start()
    {
        size = level / 10;
    }

    
    void Update()
    {
        LevelUp();
    }

    void LevelUp()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            ++level;
            SizeUp();
        }
    }

    void SizeUp()
    {
        size = 1.0f + level / 25.0f;
        this.gameObject.transform.localScale *= size;
    }
}
