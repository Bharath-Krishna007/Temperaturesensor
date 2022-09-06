//header file for WiFi library
#include<ESP8266WiFi.h>

//header file for accessing thingsSpeak cloud services
#include<ThingSpeak.h>

//header file for temperature and humidity sensor
#include <SimpleDHT.h>

//pin to which DHT sensor is connected
const int pinDHT=2;

//isntance of DHT sensor
SimpleDHT22 DHT22(pinDHT);

//channel ID of ThingSpeak channel
#define CHANNEL_ID 1690117

//Write API key of ThingSpeak channel
#define CHANNEL_API_KEY "N6MFA1BU3VOM894E"

//isntance of a WiFiClient named client
WiFiClient client;

void setup()
{
  //to begin communication using UART protocol - asynchronous communication with configurable speed
  //9600 is the Baud rate (bits per second)
  Serial.begin(9600);
  
  //to forget previously connected network
  WiFi.disconnect();
  
  Serial.print("Searching Network.");

  //to make the ESP8266 search and connect with the network with name <network name>
  WiFi.begin("Bharath","12345678");

  //loops until connection with the network is successful
  while(!(WiFi.status() == WL_CONNECTED))
  {
    Serial.print("...");
    delay(300);
  }
  Serial.println();
  Serial.println("Connected Successfully..");
  Serial.print("Your IP: ");

  //to print IP address of connected network
  Serial.println(WiFi.localIP());

  //initializing the wifi client
  ThingSpeak.begin(client);
}

void loop()
{
  float temp,humidity;
  temp = 0;
  humidity = 0;
  
  //loops until DHT22 is connected
  while(DHT22.read2(&temp,&humidity,NULL)!=0)
  {
    Serial.println("DHT22 Failed...");
    delay(2000);
  }

  //printing Temperature
  Serial.print("Temperature: ");
  Serial.print((int)temp);
  Serial.print(" degree C          ");

  //printing Humidity
  Serial.print("Humidity: ");
  Serial.print((int)humidity);
  Serial.println(" Relative Humidity in %");

  ThingSpeak.setField(1,temp);
  ThingSpeak.setField(2,humidity);
  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);

  delay(15000);

}
