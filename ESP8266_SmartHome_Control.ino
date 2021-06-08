#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#define DHTPIN 13
#define DHTTYPE DHT11
#define LAMP1_PIN 5
#define LAMP2_PIN 4
#define LAMP3_PIN 0
#define LAMP4_PIN 2
#define FAN_PIN 14
#define HEATER_PIN 12
int VIRTUAL_PIN_1;
int VIRTUAL_PIN_2;
int VIRTUAL_PIN_3;
int VIRTUAL_PIN_4;
int VIRTUAL_PIN_5;
int VIRTUAL_PIN_6;
int VIRTUAL_PIN_7;
int VIRTUAL_PIN_8;
int VIRTUAL_PIN_10;
bool n1_isPushOnApp = false;
bool n2_isPushOnApp = false;
bool n3_isPushOnApp = false;
bool n4_isPushOnApp = false;
bool n5_isPushOnApp = false;
bool n6_isPushOnApp = false;
bool n7_isPushOnApp = false;
bool n8_isPushOnApp = false;
bool n10_isPushOnApp = false;
char auth[] = "5rr5mu7i_v59RIRcpCPvRjKV6tN21EZi"; // Nhập AuthToken
char ssid[] = "Ngo To Han"; // Nhập tên WiFi
char pass[] = "19641970"; // Nhập password WiFi
int humDht = 0;
int tempDht = 0;
/*BLYNK_CONNECTED(){
  Blynk.syncAll();
}*/
BLYNK_WRITE(V1)
{
    VIRTUAL_PIN_1 = param.asInt();
    n1_isPushOnApp = true;
}
BLYNK_WRITE(V2)
{
    VIRTUAL_PIN_2 = param.asInt();
    n2_isPushOnApp = true;
}
BLYNK_WRITE(V3)
{
    VIRTUAL_PIN_3 = param.asInt();
    n3_isPushOnApp = true;
}
BLYNK_WRITE(V4)
{
    VIRTUAL_PIN_4 = param.asInt();
    n4_isPushOnApp = true;
}
BLYNK_WRITE(V5)
{
    VIRTUAL_PIN_5 = param.asInt();
    n5_isPushOnApp = true;
}
BLYNK_WRITE(V6)
{
    VIRTUAL_PIN_6 = param.asInt();
    n6_isPushOnApp = true;
}
BLYNK_WRITE(V7)
{
    VIRTUAL_PIN_7 = param.asInt();
    n7_isPushOnApp = true;
}
BLYNK_WRITE(V8)
{
    VIRTUAL_PIN_8 = param.asInt();
    n8_isPushOnApp = true;
}
BLYNK_WRITE(V10)
{
    VIRTUAL_PIN_10 = param.asInt();
    n10_isPushOnApp = true;
}
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
void setup()
{
    // Debug console
    Serial.begin(115200);
    pinMode(LAMP1_PIN, OUTPUT);
    pinMode(LAMP2_PIN, OUTPUT);
    pinMode(LAMP3_PIN, OUTPUT);
    pinMode(LAMP4_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    pinMode(HEATER_PIN, OUTPUT);
    digitalWrite(LAMP1_PIN,1);
    digitalWrite(LAMP2_PIN,1);
    digitalWrite(LAMP3_PIN,1);
    digitalWrite(LAMP4_PIN,1);
    digitalWrite(FAN_PIN,1);
    digitalWrite(HEATER_PIN,1);
    dht.begin();    // Bắt đầu đọc dữ liệu
    Blynk.begin(auth, ssid, pass);
    timer.setInterval(1000L, getDhtData);
    timer.setInterval(1000L, sendDhtData);
    timer.setInterval(100L, ctrlDevices);
    timer.setInterval(100L, ctrlAllLamp);
    timer.setInterval(1000L, autoCtrl);
}
void loop()
{
    Blynk.run();
    timer.run();         
}
void getDhtData(void)
{
    tempDht = dht.readTemperature();
    humDht = dht.readHumidity();
}
void sendDhtData(void)
{
    Blynk.virtualWrite(V11, tempDht); //Nhiệt độ với pin V10
    Blynk.virtualWrite(V12, humDht); // Độ ẩm với pin V11
}
void ctrlDevices(void)
{
    if(n1_isPushOnApp) // neu Nut nhan 1 tren App duoc nhan
    {
        digitalWrite(LAMP1_PIN, !(VIRTUAL_PIN_1)); //ghi trang thai V1 len LED
        n1_isPushOnApp = false;                  // xoa bien cap nhat
    }     
    if(n2_isPushOnApp)
    {
        digitalWrite(LAMP2_PIN, !(VIRTUAL_PIN_2));
        n2_isPushOnApp = false;
    }
    if(n3_isPushOnApp)
    {
        digitalWrite(LAMP3_PIN, !(VIRTUAL_PIN_3)); 
        n3_isPushOnApp = false;
    }
    if(n4_isPushOnApp)
    {
        digitalWrite(LAMP4_PIN, !(VIRTUAL_PIN_4));
        n4_isPushOnApp = false;
    }
    if(n7_isPushOnApp)
    {
        digitalWrite(FAN_PIN, !(VIRTUAL_PIN_7));
        n7_isPushOnApp = false;
    }
    if(n8_isPushOnApp)
    {
        digitalWrite(HEATER_PIN, !(VIRTUAL_PIN_8));
        n8_isPushOnApp = false;
    }
}
void ctrlAllLamp(void)
{
    if(n5_isPushOnApp)
    {
        digitalWrite(LAMP1_PIN, 0);
        Blynk.virtualWrite(V1, 1);
        digitalWrite(LAMP2_PIN, 0);
        Blynk.virtualWrite(V2, 1);
        digitalWrite(LAMP3_PIN, 0);
        Blynk.virtualWrite(V3, 1);
        digitalWrite(LAMP4_PIN, 0);
        Blynk.virtualWrite(V4, 1);   
        n5_isPushOnApp = false;
    }
    if(n6_isPushOnApp)
    {
        digitalWrite(LAMP1_PIN, 1);
        Blynk.virtualWrite(V1, 0);
        digitalWrite(LAMP2_PIN, 1);
        Blynk.virtualWrite(V2, 0);
        digitalWrite(LAMP3_PIN, 1);
        Blynk.virtualWrite(V3, 0);
        digitalWrite(LAMP4_PIN, 1);
        Blynk.virtualWrite(V4, 0);
        n6_isPushOnApp = false;
    }   
}
void autoCtrl(void)
{
    if(VIRTUAL_PIN_10)
    {
        if(tempDht >= 35)
        {
            digitalWrite(FAN_PIN, 0);
            Blynk.virtualWrite(V7, 1);
        }
        else
        {
            digitalWrite(FAN_PIN, 1);
            Blynk.virtualWrite(V7, 0);
        }
            
        if(tempDht <= 16)
        {
            digitalWrite(HEATER_PIN, 0);
            Blynk.virtualWrite(V8, 1);
        }
        else
        {
            digitalWrite(HEATER_PIN, 1);
            Blynk.virtualWrite(V8, 0);
        }        
    }
}
