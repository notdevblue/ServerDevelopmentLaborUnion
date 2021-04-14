using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using WebSocketSharp;
public class Connecti : MonoBehaviour
{
    public string url = "ws://localhost";
    public int port = 56789;
    private WebSocket webSocket;

    void Start()
    {
        webSocket = new WebSocket(url + ":" + port);
        webSocket.Connect();
    }

    
    void Update()
    {
        webSocket.OnMessage += (sender, e) =>
        {
            Debug.Log(e);
        };
    }
}
