const WebSocket = require('ws');
const port = 56789;
const ws = new WebSocket.Server({ port }, () => {
    console.log("서버 켜짐");
});

var msg = "Hello";

ws.on("connection", socket => {
    socket.send("hellomsg", msg);
});