const express = require("express");
const bodyParser = require("body-parser");
const path = require("path");

const app = express();
const PORT = process.env.PORT || 3000;

app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, "../public")));

app.get("/", (req, res) => {});

app.post("/login", (req, res) => {
    res.redirect("/login");
});
app.post("/message", (req, res) => {
  const message = req.body;
  console.log(message);
  res.status(200).send([
    { id: 1, msg: "hello" },
    { id: 2, msg: "hi" },
  ]);
});


app.listen(PORT, () => {
  console.log(`running on port ${PORT}`);
});
