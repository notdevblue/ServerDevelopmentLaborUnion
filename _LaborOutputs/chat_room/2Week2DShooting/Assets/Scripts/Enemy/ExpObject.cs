using UnityEngine;

public class ExpObject : MonoBehaviour
{

    [SerializeField]
    private int hp = 5;

    private void Start()
    {
        
    }

    private void OnEnable()
    {
        hp = 5;
        //나중에 hp바가 생긴다면 여기서초기화해준다.
    }

    private void OnCollisionEnter2D(Collision2D other)
    {
        if(other.gameObject.CompareTag("PLAYER")) //태그는 임시롤 만든 ㄴ플레이어로 해두었다. 나중에 불렛으로 바꾸면댈듯함.
        {
            hp--;
            if(hp <= 0)
            {
                ExpPoolManager.instance.InsertQueue(gameObject);
                GameManager.instance.playerLevelup.curExp += 10;
            }
        }
        else if(other.gameObject.CompareTag("ENEMY")) //겹치면 다시 생성되게 해놨는데 아마도 나중에 바꿀듯..?
        {
            ExpPoolManager.instance.InsertQueue(gameObject);
        }
    }

}
