using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerLevelup : MonoBehaviour
{
    #region 임시 변수 포함된 변수들

    private const int MAXLEVEL = 10;

    private int   level = 1; // 지금 래벨
    private float size  = 1; // scale *= size;

    private bool _levelUp = false;
    public  bool IsLevelUp { get { return _levelUp; }
                             set { if (!value) _levelUp = value; } } // 스텟 하나 증가시키는 용도. 외부에서 true 세팅은 못함

    public           int[] expData   = new int[MAXLEVEL]; // 렙업 요구 경험치
    private readonly int[] reqExpArr = new int[MAXLEVEL]; // 실제 사용하는 경험치 확인 배열

    public int curExp { get; set; } // 현제 경험치


    #endregion


    void Start()
    {
        SetRequireExp();
    }

    
    void Update()
    {

#if UNITY_EDITOR
        if (Input.GetKeyDown(KeyCode.Space)) // 테스트용
        {
            LevelUp();
        }
#else
        LevelUp();
#endif

    }

    void LevelUp()
    {
        if (level == MAXLEVEL) return;

        if(curExp >= reqExpArr[level])
        {
            _levelUp = true;
            ++level;
            SizeUp();
        }
    }

    void SizeUp()
    {
        size = 1.0f + level / 50.0f; // 대충 적당하게 공식만들음
        this.gameObject.transform.localScale *= size;
    }

    void SetRequireExp()
    {
        for(int idx = 0; idx < MAXLEVEL; ++idx)
        {
            reqExpArr[idx] = expData[idx];
        }
    }
}
