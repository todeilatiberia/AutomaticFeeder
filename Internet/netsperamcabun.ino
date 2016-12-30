#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {
0xD0, 0x33, 0x11, 0x52, 0x6C, 0xAE }; //Specify the MAC address that's on the Ethernet shield
IPAddress ip(192,168,0,177); //Specify the IP address to assign to the Arduino server
EthernetServer server(80); //Specify the port that the server will use (Since it will be HTTP, you can leave it as 80)

void setup() {
// Open serial communications and wait for port to open:
Serial.begin(9600);
while (!Serial) {
 // wait for serial port to connect. Needed for Leonardo only
}
Ethernet.begin(mac, ip); //Here we attempt to connect by Ethernet shield
server.begin();
Serial.print("server is at ");
Serial.println(Ethernet.localIP());
}

void loop() {
EthernetClient client = server.available(); //Monitor whether there is an external connection to the server
if (client) {
Serial.println("new client");
// an http request ends with a blank line
boolean currentLineIsBlank = true;
while (client.connected()) {
if (client.available()) {
char c = client.read();
Serial.write(c);
// if you've gotten to the end of the line (received a newline
// character) and the line is blank, the http request has ended,
// so you can send a reply
if (c == 'n' && currentLineIsBlank) {
// send a standard http response header
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close"); // the connection will be closed after completion of the response
client.println("Refresh: 5"); // refresh the page automatically every 5 sec
client.println();
client.println("");
client.println("");
// output the value of each analog input pin
for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
int sensorReading = analogRead(analogChannel);
client.print("analog input ");
client.print(analogChannel);
client.print(" is ");
client.print(sensorReading);
client.println("");
}
client.println("");
break;
}
if (c == 'n') {
// you're starting a new line
currentLineIsBlank = true;
}
else if (c != 'r') {
// you've gotten a character on the current line
currentLineIsBlank = false;
}
}
}
// give the web browser time to receive the data
delay(1);
// close the connection:
client.stop();
Serial.println("client disonnected");
}
}
