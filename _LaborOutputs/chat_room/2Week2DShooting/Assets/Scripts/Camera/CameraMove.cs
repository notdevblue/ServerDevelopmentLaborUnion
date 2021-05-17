using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour
{
    private Vector3 mainCamPos;
    private void Awake()
    {

    }

    private void Update()
    {
        mainCamPos = GameManager.instance.player.transform.position;
        mainCamPos.z = -10;
        transform.position = mainCamPos;
    }
}
