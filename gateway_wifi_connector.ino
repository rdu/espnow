#include <ESP8266WiFi.h>
#include <Wire.h>

extern "C"
{
#include "user_interface.h"
}

#define i2c_slave_address 88

void setup()
{
    Serial.begin(115200);
    Serial.println("starting gateway wifi connector...");
    Wire.begin(i2c_slave_address);
    Serial.print("registered i2c address: ");
    Serial.println(i2c_slave_address);
    Wire.onReceive(receiveEvent);
}

void receiveEvent(int count)
{
    Serial.print("received message of #");
    Serial.print(count);
    Serial.println("bytes");

    byte mac[6];
    byte message[250];
    while (Wire.available())
    {
        int pos = 0;
        for (int i = 0; i < 6)
        {
            mac[pos++] = Wire.read();
        }

        Serial.println("received mac address");

        int len = Wire.read();

        Serial.print("received length of");
        Serial.println(len);

        pos = 0;
        for (int i = 0; i < len)
        {
            message[pos++] = Wire.read();
        }
        Serial.println("message read...");
        String str = String(message);
        Serial.println("message:");
        Serial.println(str);
    }
}

void loop()
{
}