#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include "DHT.h"
#include "index.h"
#include "setting.h"


#define DHTPIN D4
#define SOIL_MOIST_1_PIN A0 
// Relay, nút nhấn
#define PUMP_ON_BUTTON D5   //Nút có sẵn trên kit
#define LAMP_ON_BUTTON D6   //Nút có sẵn trên kit
#define AUTO_BUTTON D3

#define PUMP_PIN D1   //Bom
#define LAMP_PIN D2   //Den

#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321

int DRY_SOIL = 30;
int WET_SOIL = 40;
int COLD_TEMP = 33;
int HOT_TEMP = 39;

String DRY_SOIL1;
String WET_SOIL1;
String COLD_TEMP1;
String HOT_TEMP1;
WiFiUDP Udp;
DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);
LiquidCrystal_I2C lcd(0x27,16,2);

String Lamp,Motor,Auto;
int humDHT;
int tempDHT;
int soilMoist;

boolean pumpStatus = 0;
boolean lampStatus = 0;
boolean autoStatus = 0;


int getSoilMoist()
{
  int i = 0;
  int anaValue = 0;
  for (i = 0; i < 10; i++)  //
  {
    anaValue += analogRead(SOIL_MOIST_1_PIN); //Đọc giá trị cảm biến độ ẩm đất
    delay(50);   // Đợi đọc giá trị ADC
  }
  anaValue = anaValue / (i);
  anaValue = map(anaValue, 1023, 0, 0, 100); 
  return anaValue;
}
void readSensors(void)
{
  tempDHT = dht.readTemperature();   //Đọc nhiệt độ DHT22
  humDHT = dht.readHumidity();       //Đọc độ ẩm DHT22
  soilMoist = getSoilMoist();        //Đọc cảm biến độ ẩm đất
}

void printData(void)
{
  Serial.print("Nhiet do: ");
  Serial.print(tempDHT);
  Serial.print(" *C\t");
  Serial.print("Do am: ");
  Serial.print(humDHT);
  Serial.print(" %\t");
  Serial.print("Do am dat: ");
  Serial.print(soilMoist);
  Serial.println(" %\t"); 
  Serial.print("Den: ");
  Serial.print(Lamp);
  Serial.print(" \t");   
  Serial.print("May bom: ");
  Serial.print(Motor);
  Serial.print(" \t");     
  Serial.print("Auto: ");
  Serial.print(autoStatus);
  Serial.print(" \t");
}
void aplyCmd1(){
  if (autoStatus == 0) off_auto();
  if (autoStatus == 1) on_auto();
}
void aplyCmd()
{
  if (pumpStatus == 0) digitalWrite(PUMP_PIN, LOW);
  if (pumpStatus == 1) digitalWrite(PUMP_PIN, HIGH);

  if (lampStatus == 0) digitalWrite(LAMP_PIN, LOW);
  if (lampStatus == 1) digitalWrite(LAMP_PIN, HIGH);
}
boolean debounce(int pin)
{
  boolean state;
  boolean previousState;
  const int debounceDelay = 60;
  previousState = digitalRead(pin);
  for (int counter = 0; counter < debounceDelay; counter++)
  {
    delay(1);
    state = digitalRead(pin);
    if (state != previousState)
    {
      counter = 0;
      previousState = state;
    }
  }
  return state;
}
void readLocalCmd()
{

  boolean digiValue = debounce(LAMP_ON_BUTTON);
  if (!digiValue)
  {
    lampStatus = !lampStatus;
    aplyCmd();
  }
  digiValue = debounce(PUMP_ON_BUTTON);
  if (!digiValue)
  {
    pumpStatus = !pumpStatus;
    aplyCmd();
  }
  digiValue = debounce(AUTO_BUTTON);
  if (!digiValue)
  {
    autoStatus = !autoStatus;
    aplyCmd1();
  }
}

void Check(){
  if (pumpStatus == 1) Motor ="ON";
  if (pumpStatus == 0) Motor ="OFF";

  if (lampStatus == 1) Lamp ="ON";
  if (lampStatus == 0) Lamp ="OFF";

  if (autoStatus == 1) Auto ="ON";
  if (autoStatus == 0) Auto ="OFF";
}
void on_D2(){
  lampStatus = 1;
  aplyCmd();
}
void off_D2(){
  lampStatus = 0;
  aplyCmd();
}
void on_D5(){
  pumpStatus = 1;
  aplyCmd();
}
void off_D5(){
  pumpStatus = 0;
  aplyCmd();
}
void on_D1(){
  autoStatus = 1;
  aplyCmd1();
}
void off_D1(){
  autoStatus = 0;
  aplyCmd1();
}
void on_auto(){
 
 if (soilMoist < DRY_SOIL) 
  {
    pumpStatus = 1;
    aplyCmd();
  }
  if (soilMoist > WET_SOIL) 
  {
    pumpStatus = 0;
    aplyCmd();
  }
 
if (tempDHT < COLD_TEMP) 
  {
    lampStatus = 1;
        aplyCmd();
  }
  if (tempDHT > HOT_TEMP) 
  {
    lampStatus = 0;
        aplyCmd();
  }
}
void off_auto(){
}

void get_statusD2D5(){
  String d1,d2,d5;
  if(digitalRead(LAMP_PIN)==1){
    d2 = "ON";
  }else{
    d2 = "OFF";
  }
  if(digitalRead(PUMP_PIN)==1){
    d5 = "ON";
  }else{
    d5 = "OFF";
  }
  if(autoStatus ==1){
    d1 = "ON";
  }else{
    d1 = "OFF";
  }
  //String s = "{\"D2\": \""+ d1 +"\",\"D5\": \""+ d2 +"\"}";
  String s = "{\"D2\": \""+ d2 +"\",\"D5\": \""+ d5 +"\",\"D1\": \""+ d1 +"\",\"temp\": \""+ tempDHT +"\",\"hum\": \""+ humDHT +"\",\"soil\": \""+ soilMoist +"\"}";
   server.send(200,"application/json",s);
}
void display_lcd(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(tempDHT);
//  lcd.print("C");
  lcd.setCursor(5,0);
  lcd.print("H:");
  lcd.print(humDHT);
//  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("S:");
  lcd.print(soilMoist);
//  lcd.print("%");
  
  lcd.setCursor(5,1);
  lcd.print("L:");
  lcd.print(Lamp);
//  lcd.print("C");
  lcd.setCursor(11,1);
  lcd.print("M:");
  lcd.print(Motor);
//  lcd.print("%");
  lcd.setCursor(10,0);
  lcd.print("A:");
  lcd.print(Auto);
//  lcd.print("%");
  lcd.display();
}
void setup1() {
   server.send(200, "text/html", "Update successful");
   COLD_TEMP1 = server.arg("COLD_TEMP1");
   COLD_TEMP = COLD_TEMP1.toInt();
   HOT_TEMP1 = server.arg("HOT_TEMP1");
   HOT_TEMP = HOT_TEMP1.toInt();
   DRY_SOIL1 = server.arg("DRY_SOIL1");
   DRY_SOIL = DRY_SOIL1.toInt();
   WET_SOIL1 = server.arg("WET_SOIL1");
   WET_SOIL = WET_SOIL1.toInt();
   Serial.println("COLD_TEMP = ");
   Serial.println(COLD_TEMP);
    Serial.println("HOT_TEMP = ");
   Serial.println(HOT_TEMP);
      Serial.println("DRY_SOIL = ");
   Serial.println(DRY_SOIL);
      Serial.println("WET_SOIL = ");
   Serial.println(WET_SOIL);
}
void setup() {
Wire.begin(D3,D7);
lcd.init();
lcd.clear();
lcd.backlight();

int cnt = 0;
  //Khởi tạo baud 115200
  Serial.begin(115200);
  //Mode wifi là station
  WiFi.mode(WIFI_STA);
  //Chờ kết nối
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(cnt++ >= 10){
       WiFi.beginSmartConfig();
       while(1){
           delay(1000);
           //Kiểm tra kết nối thành công in thông báo
           if(WiFi.smartConfigDone()){
             Serial.println("SmartConfig Success");
             break;
           }
       }
    }
  }
  
  Serial.println("");
  Serial.println("");
  
  WiFi.printDiag(Serial);
  
  // Khởi tạo server
  Udp.begin(49999);
  Serial.println("Server started");

  // In địa chỉ IP
  Serial.println(WiFi.localIP());

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(PUMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(LAMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(AUTO_BUTTON, INPUT_PULLUP);
  aplyCmd();
  aplyCmd1();  
  dht.begin();
  readSensors(); // Khởi tạo đọc cảm biến

  server.on("/",[](){server.send_P(200,"text/html", MAIN_page);});
  server.on("/setting",[](){server.send_P(200,"text/html", MAIN_page1);});

  server.on("/onD2",on_D2);
  server.on("/offD2",off_D2);
  server.on("/onD5",on_D5);
  server.on("/offD5",off_D5);
  server.on("/onD1",on_D1);
  server.on("/offD1",off_D1);
  server.on("/getstatusD2D5",get_statusD2D5);
  server.on("/setup1",setup1);
  server.begin();
}

void loop() {
  server.handleClient();
   Udp.parsePacket();
  //In IP của ESP8266
  while(Udp.available()){
    Serial.println(Udp.remoteIP());
    Udp.flush();
    delay(5);
  }
  display_lcd();

  readSensors();
  aplyCmd();
  aplyCmd1();
  Check();
  readLocalCmd();
  printData();
  HTTPClient http;    //Declare object of class HTTPClient
  String  postData;
  postData = "Nhiet_Do=" + String(tempDHT)+ "&Do_Am=" + String(humDHT) + "&Do_Am_Dat=" + String(soilMoist)+ "&Den=" + Lamp + "&Bom=" + Motor ;
  http.begin("http://192.168.1.16:8077/test1/postdemo.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCode = http.POST(postData);   //Send the request  
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();
}
