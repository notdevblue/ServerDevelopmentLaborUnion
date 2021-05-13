const WebSocket = require('ws');
const Vector3 = require('./Vector3');
const port = 32000;
const wsService = new WebSocket.Server({ port }, () => {
    console.log("웹소켓 서버 스타트");
});

const State = {
    IN_LOGIN: 0,
    IN_LOBBY: 1,
    IN_CHAT: 2
}

//데이터 전송간 명령어와 페이로드 구분해주는 함수
const getPayload = str => {
    let idx = str.indexOf(":");
    let op = str.substr(0, idx);
    let payload = str.substr(idx + 1);
    return { op, payload };
};

//wsService는 내부에 clients라는 속성을 가지고 있고 해당 
//속성을 이용해서 브로드캐스트등을 구현할 수 있다.

wsService.on("connection", socket => {
    socket.send("CHAT:System:Welcome To my Chat server");
    socket.state = State.IN_LOBBY;
    socket.on("message", msg => {
        const data = JSON.parse(msg);

        if (data.type === "enterRoom") {

        }
        if (data.type === "Chat") {
            wsService.clients.forEach(x => {
                if (x.room == data.room) {
                    x.send(data.msg)
                }
            });
        }
        if (data.type === "Transform") {
            TransformHandler();
        }
    });
});

wsService.on('listening', () => {
    console.log(`server listen on ${port}`);
});