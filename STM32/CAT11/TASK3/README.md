# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 11

**NAME OF EXP:** Node-RED as a Second HTTP Client of STM32/ESP8266 HTTP Server

**HARDWARE SETUP / PLATFORM:** STM32CubeMX + Keil MDK + STM32F401RE Development Board + Wemos ESP8266 Wi-Fi Module + Node-RED

---

## TASK 10E – Node-RED as a Second HTTP Client of STM32/ESP8266 HTTP Server

### 1. Circuit Diagram

The experiment demonstrates HTTP communication between Node-RED and an STM32-based HTTP server using the Wemos ESP8266 Wi-Fi module.

The STM32F401RE communicates with the ESP8266 through USART6. The ESP8266 connects to the Wi-Fi network and acts as a TCP server on port 80. Node-RED acts as a second HTTP client and sends requests to the STM32/ESP8266 server.

**Hardware Components:**

- **Development Board:** STM32F401RE
- **Wi-Fi Module:** Wemos ESP8266
- **UART Peripheral:** USART6
- **Communication Interface:** UART Serial Communication
- **TCP Server Port:** 80
- **HTTP Client:** Node-RED running on a computer

**Connections:**

- STM32 USART6 TX → Wemos ESP8266 RX
- STM32 USART6 RX → Wemos ESP8266 TX
- STM32 GND → Wemos GND
- Ensure that the ESP8266 is supplied with a suitable 3.3V power source.

**UART Configuration:**

- Baud Rate: 115200
- Word Length: 8 Bits
- Stop Bits: 1
- Parity: None
- Mode: Transmitter and Receiver

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

The experiment demonstrates the use of Node-RED as a second HTTP client to communicate with the HTTP server implemented using STM32F401RE and Wemos ESP8266.

The STM32 communicates with the ESP8266 through USART6 using AT commands. The ESP8266 connects to the Wi-Fi network and starts a TCP server on port 80.

Node-RED is configured with three nodes connected in the following sequence:

**Inject → HTTP Request → Debug**

1. **Inject Node:** Triggers the HTTP request manually.
2. **HTTP Request Node:** Sends an HTTP GET request to the ESP8266 server using the URL `http://<ESP8266_IP>/`.
3. **Debug Node:** Displays the HTTP response received from the STM32.

When Node-RED triggers the request, the ESP8266 forwards the incoming HTTP request to the STM32 through UART using the `+IPD` notification.

The STM32 extracts the connection ID, generates a random uppercase letter between A and Z, and creates a dynamic HTML webpage containing the heading "STM32 IoT Node", the message "Hello from STM32", and the generated random letter.

The HTTP response is transmitted back through the ESP8266 to Node-RED using the `AT+CIPSEND` command. Node-RED receives the response and displays it in the Debug window.

**Pseudocode:**

1. Initialize the HAL library.
2. Configure the system clock.
3. Initialize GPIO peripherals.
4. Initialize USART6 with a baud rate of 115200.
5. Wait for 2 seconds to allow the ESP8266 to initialize.
6. Test ESP8266 communication using the `AT` command.
7. Configure the ESP8266 in Wi-Fi Station mode using `AT+CWMODE=1`.
8. Connect to the Wi-Fi network using `AT+CWJAP`.
9. Retrieve the ESP8266 IP address using `AT+CIFSR`.
10. Enable multiple connections using `AT+CIPMUX=1`.
11. Start the TCP server on port 80 using `AT+CIPSERVER=1,80`.
12. Configure the Node-RED flow using Inject, HTTP Request, and Debug nodes.
13. Set the HTTP Request node URL to `http://<ESP8266_IP>/`.
14. Trigger the Inject node to send an HTTP GET request.
15. Receive the incoming HTTP request through USART6.
16. Extract the TCP connection ID from the `+IPD` notification.
17. Generate a random uppercase letter and construct an HTML webpage.
18. Create an HTTP response with the appropriate headers and webpage content.
19. Send the response to the ESP8266 using `AT+CIPSEND`.
20. Close the client connection using `AT+CIPCLOSE`.
21. Display the received HTTP response in the Node-RED Debug window.

**Code Base:**

The STM32 HTTP server implementation uses the following STM32 HAL functions and C library functions:

- `HAL_Init()` – Initializes the HAL library.
- `HAL_UART_Init()` – Initializes the USART6 peripheral.
- `HAL_UART_Transmit()` – Transmits AT commands and HTTP responses.
- `HAL_UART_Receive()` – Receives incoming HTTP requests.
- `HAL_GetTick()` – Returns the system tick count in milliseconds.
- `HAL_Delay()` – Introduces delays.
- `sendAT()` – Sends AT commands and checks ESP8266 responses.
- `waitForPrompt()` – Waits for the `>` prompt before transmitting data.
- `receiveRequest()` – Receives incoming HTTP client requests.
- `strstr()` – Searches for the `+IPD` notification and response strings.
- `sscanf()` – Extracts the TCP connection ID.
- `snprintf()` – Generates HTML content, AT commands, and HTTP response headers.
- `rand()` – Generates a random uppercase letter.

**Node-RED Flow Configuration:**

- **Inject Node:** Used to manually trigger the HTTP request.
- **HTTP Request Node:** Configured with the ESP8266 IP address and HTTP GET method.
- **Debug Node:** Displays the HTTP response received from the STM32 HTTP server.

### 3. Inference

Node-RED successfully acts as a second HTTP client and communicates with the HTTP server implemented using STM32F401RE and Wemos ESP8266.

When the Inject node is triggered, Node-RED sends an HTTP GET request to the ESP8266 IP address. The STM32 processes the request and generates a dynamic HTML response containing a randomly generated uppercase letter.

The received HTTP response is displayed in the Node-RED Debug window.

This experiment demonstrates HTTP client-server communication, Node-RED flow configuration, UART-based communication, dynamic webpage generation, and IoT integration using STM32, ESP8266, and Node-RED.
