using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerLevelup : MonoBehaviour
{
    #region 임시 변수
    public int level = 1;
    public int[] reqExpArr = new int[10]; // 10랩까지만 만들레요.
    public int curExp = 0;

    private float size = 1;

    public bool levelUP = true;


    #endregion


    void Start()
    {
        size = level / 10;
    }

    
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Space)) // 경험치보다 높으면
        {
            LevelUp();
        }
    }



    

    void LevelUp()
    {
        if (level == 10) return;

        if(curExp >= reqExpArr[level])
        {
            ++level;
            SizeUp();
        }
        else
        {
            
        }
    }

    void SizeUp()
    {
        size = 1.0f + level / 25.0f;
        this.gameObject.transform.localScale *= size;
    }
}
