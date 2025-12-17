const brokerUrl = "wss://broker.masihch.com:443/mqtt";
const username = "freeplan";
const password = "12345678";

const statusBox = document.getElementById("statusBox");
const statusText = document.getElementById("statusText");
const connectBtn = document.getElementById("connectBtn");
const topicInput = document.getElementById("topicInput");

let client;

connectBtn.addEventListener("click", () => {
  const topic = topicInput.value.trim() || "sensor/sound";

  if (Notification.permission !== "granted") {
    Notification.requestPermission().then(permission => {
      if (permission !== "granted") {
        alert("Notifications are blocked. Please enable them in browser settings.");
      }
    });
  }

  client = mqtt.connect(brokerUrl, {
    username: username,
    password: password
  });

  client.on("connect", () => {
    console.log("Connected to MQTT broker");
    statusBox.className = "status-normal";
    statusBox.innerHTML = "✅ Connected to broker";
    statusText.innerHTML = "Subscribed to topic: " + topic;

    client.subscribe(topic, (err) => {
      if (!err) {
        console.log("Subscribed to", topic);
      }
    });
  });

  client.on("message", (t, message) => {
    if (t === topic) {
      const msg = message.toString();
      console.log("Received:", msg);

      if (msg === "detect") {
        statusBox.className = "status-alert";
        statusBox.innerHTML = "⚠️ Abnormal sound detected!";
        statusText.innerHTML = "Sound event detected (crying, breaking, etc.)";
        showNotification("⚠️ Sound Alert", "Abnormal sound detected!");
      } else if (msg === "nodetect") {
        statusBox.className = "status-normal";
        statusBox.innerHTML = "✅ No abnormal sound detected";
        statusText.innerHTML = "Environment is quiet";
        showNotification("✅ Normal", "No abnormal sound detected");
      }
    }
  });
});

function showNotification(title, body) {
  if (Notification.permission === "granted") {
    new Notification(title, { body: body });
  }
}
