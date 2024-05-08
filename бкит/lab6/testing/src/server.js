const express = require("express");

const app = express();

app.get("/", (request, response) => {
  response.send("Hello, world!");
});

users = [
  { id: 1, username: "adam" },
  { id: 2, username: "jack" },
];
app.get("/api/users", (request, response) => {
  response.send(users);
});

app.get("/api/products", (request, response) => {
  response.send([
    { id: 123, name: "apple", price: 120 },
    { id: 234, name: "bananas", price: 68 },
  ]);
});

app.get("/api/users/:id", (request, response) => {
  console.log(request.params);
  const parsedId = parseInt(request.params.id);
  console.log(parsedId);
  if (isNaN(parsedId)) return response.status(400).send({ msg: "Invalid id" });

  const findUser = users.find((user) => user.id === parsedId);
  if (!findUser) return response.redirect("/api/users");

  return response.send(findUser);
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Running on port ${PORT}`);
});
