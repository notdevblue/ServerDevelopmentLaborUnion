const WebSocket = require('ws');
const port = 32000;
const wsService = new WebSocket.Server({ port }, () => {
    console.log("웹소켓 서버 스타트");
});

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
    socket.on("message", msg => {

        let data = getPayload(msg);

        if (data.op === "CHAT") {
            wsService.clients.forEach(x => x.send(msg));
        }
    });
});

wsService.on('listening', () => {
    console.log(`server listen on ${port}`);
});