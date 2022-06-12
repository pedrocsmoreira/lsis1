#ifndef MQTT_H
#define MQTT_H
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

void setupWIFI(char* ssid, char* password);
void callback(char* topic, byte* message, unsigned int length);
void reconnect();



#endif
