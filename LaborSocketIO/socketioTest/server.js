const app = require('express')();
const server = require('http').createServer(app);
const io = require('socket.io')(server);

app.get("/test", (req, res) => {
    res.sendFile(__dirname + "/index.html");
});

io.on("connection", socket => {
    console.log(socket.id + " connected");

    socket.Emit("news", "Hello");

    socket.on("msg", data => {
        console.log(data);
    })



    socket.on("disconnect", () => {
        console.log("disconnected");
    });
});

server.listen(56789, () => {
    console.log("서버 실행됨");
});