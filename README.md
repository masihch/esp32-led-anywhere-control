# IOT-MQTT-Web-Dashboards
In this repository, I plan to provide real time smart web dashboards that work with the MQTT protocol. They will be available both as open source code for development and as quick access instances hosted on my servers, so you can more easily test and deploy your own projects.

-  **🌐Global Control** from anywhere.
-  **💻Web Dashboards** For applied projects. 
-  **⛓️‍💥Used Free Public MQTT Broker** for connection.
-  **⚙️Expandable** for commercial projects.
## Connection solution
For these projects, the mqtt protocol is used for connection. I have previously published information about the free mqtt broker on my personal site.[MQTT broker](https://masihch.com/mqtt-public-broker-free-test-server/)
## 1.Basic Control [Dashboard](https://lab.masihch.com/control-esp32-from-anywhere-in-the-world/index.html)
A simple graphical dashboard that connects to an MQTT broker and sends ON/OFF messages to a topic. The device on the other side reacts by changing the state of a GPIO pin.

### 🚀 How to use

- Connect to the broker by clicking on the button (connect to broker)
- Select a topic to send messages
- Use the toggle button to send messages on and off
- On the device side, you must subscribe to the dashboard topic.
- Manage messages received from the dashboard side

### 🛠️ Development
You can develop this dashboard for your own project or commercialize it. I have included the dashboard side scripts for the web as well as a code sample for esp32 : [Dashboard scripts](Control)

```bash
git clone https://github.com/masihch/esp32-led-anywhere-control.git
cd esp32-led-anywhere-control

```
-Then,Open the program in the ESP32 folder and upload it to the esp32
-Open this URL and start controlling! [Dahboard](https://lab.masihch.com/control-esp32-from-anywhere-in-the-world/index.html)
## View of the project
![ESP32-Dash](https://github.com/masihch/iot-mqtt-web-dashboards/blob/main/images/view.webp)
![Dashboard-control](https://github.com/masihch/iot-mqtt-web-dashboards/blob/main/images/web-dashboard.webp)
![Dashboard-monitoring](https://github.com/masihch/iot-mqtt-web-dashboards/blob/main/images/web-monitor-dashboard.webp)
