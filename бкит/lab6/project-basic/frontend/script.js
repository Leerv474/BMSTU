const messageContainer = document.getElementById("message-container");
const messageForm = document.getElementById("send-container");
const messageInput = document.getElementById("message-input");

const username = prompt("What is your name?")
try {
  const response = await fetch("/new-user", {method: 'POST'});
  const data = await response.json();
  appendMessage("You joined")
} catch (error) {
  console.error("Error:", error);
}

socket.on("chat-message", (data) => {
  appendMessage(`${data.username}: ${data.message}`)
});
socket.on("user-connected", (username) => {
  appendMessage(`${username} connected`)
});
socket.on("user-disconnected", (username) => {
  appendMessage(`${username} disconnected`)
});

messageForm.addEventListener("submit", (e) => {
  e.preventDefault();
  const message = messageInput.value;
  appendMessage(`You: ${message}`);
  socket.emit("send-chat-message", message);
  messageInput.value = "";
});

function appendMessage(message) {
  const messageElement = document.createElement("div")
  messageElement.innerText = message
  messageContainer.append(messageElement)
}
