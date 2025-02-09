#include <Arduino.h>

// Put function declarations here:
void updateSerial()
{
    delay(500);
    while (Serial.available())
    {
        Serial2.write(Serial.read()); // Forward what Serial received to Software Serial Port
    }
    while (Serial2.available())
    {
        Serial.write(Serial2.read()); // Forward what Software Serial received to Serial Port
    }
}

void setup()
{
    // Put your setup code here, to run once:
    Serial.begin(9600);
    Serial2.begin(115200);

    Serial.println("Initialising");

    Serial2.println("AT");        // Once the handshake test is successful, it will return OK
    Serial2.println("AT+CSQ");    // Signal quality test, value range 0-31. 31 is the best
    Serial2.println("AT+CCID");   // Read SIM information to confirm whether the SIM is plugged
    Serial2.println("AT+CREG?");  // Check whether it has registered on the network
    Serial2.println("AT+COPS?");  // Check whether it has registered in the network

    updateSerial();
}

void loop()
{
    // Put your main code here, to run repeatedly:
    // Serial.println("Response:");
    // Serial2.println("AT");
    updateSerial();
}
