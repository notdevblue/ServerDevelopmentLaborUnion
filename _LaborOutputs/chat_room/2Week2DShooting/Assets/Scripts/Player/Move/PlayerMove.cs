using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    private Rigidbody2D rigid;
    private Vector2 vec;
    private Vector3 mousePos;
    public GameObject testObj;

    [Header("이동 관련 변수")]
    public float speed = 5;

    private void Start()
    {
        rigid = GetComponent<Rigidbody2D>();
        vec = new Vector2();
    }

    private void Update()
    {
        Move();
        Rotation();
    }

    void Move()
    {
        vec.Set(GameManager.instance.pi.xMove * speed, GameManager.instance.pi.yMove * speed);
        rigid.velocity = vec;
    }

    void Rotation()
    {
        mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);         // 마우스 포지션을 메인 카메라 기준으로 바꾸고 월드 포지션으로 체인지 해줫슴
        Vector3 v = transform.position - mousePos;                              // 플레이어와 마우스의 위치를 뺴서 서로의 거리를 구함
        float r = Mathf.Atan2(v.y, v.x) * Mathf.Rad2Deg;                        // AngleAxis를 통해서 각도를 구한다
        transform.rotation = Quaternion.AngleAxis(r, Vector3.forward);          // 구한 각도 만큼 z값을 움직여 준다
        testObj.transform.position = mousePos;                                  // Gizmo로 Scene에 보이게 하는 거 ( 디버깅 용도 코드에요 )
    }
}
