

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
ESP8266WebServer server(80);
#include "index.h"

#define DHTPIN D3    // Chân DATA nối với D3
//#define LDR_PIN A0    // Chân PE3 nối với chân OUT cảm biến as
#define SOIL_MOIST_1_PIN A0 // Chân PE4 nối với cảm biến độ ẩm
// Relay, nút nhấn
#define PUMP_ON_BUTTON D6   //Nút có sẵn trên kit
#define LAMP_ON_BUTTON D7   //Nút có sẵn trên kit
#define SENSORS_READ_BUTTON D4

#define PUMP_PIN D5   //Bom
#define LAMP_PIN D2   //Den
// Uncomment loại cảm biến bạn sử dụng, nếu DHT11 thì uncomment DHT11 và comment DHT22
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DRY_SOIL      66
#define WET_SOIL      88
#define COLD_TEMP     15
#define HOT_TEMP      24
#define TIME_PUMP_ON  15
#define TIME_LAMP_ON  15


/* Set these to your desired credentials. */
const char *ssid = "vnpt.luu.thao.";  //ENTER YOUR WIFI SETTINGS
const char *password = "123123123";

//Web/Server address to read/write from 
//const char *host = "192.168.100.5";   //https://circuits4you.com website or IP address of server



// Biến lưu các giá trị cảm biến
int humDHT;
int tempDHT;
//int lumen;
int soilMoist;
// Biến lưu trạng thái bơm
boolean pumpStatus = 0;
boolean lampStatus = 0;

int timePumpOn = 10; // Thời gian bật bơm nước
// Biến cho timer
long sampleTimingSeconds = 50; // ==> Thời gian đọc cảm biến (s)
long startTiming = 0;
long elapsedTime = 0;
// Khởi tạo cảm biến
DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 s.replace("@@temp@@",String(tempDHT));  
 s.replace("@@hum@@",String(humDHT));  
 s.replace("@@soil@@",String(soilMoist));  
 server.send(200, "text/html",s ); //Send web page
}
void aplyCmd()
{
  if (pumpStatus == 0) digitalWrite(PUMP_PIN, LOW);
  if (pumpStatus == 1) digitalWrite(PUMP_PIN, HIGH);

  if (lampStatus == 0) digitalWrite(LAMP_PIN, LOW);
  if (lampStatus == 1) digitalWrite(LAMP_PIN, HIGH);
}
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
  anaValue = map(anaValue, 1023, 0, 0, 100); //Ít nước:0%  ==> Nhiều nước 100%
  return anaValue;
}
void readSensors(void)
{
 // tempDHT = dht.readTemperature();   //Đọc nhiệt độ DHT22
 // humDHT = dht.readHumidity();       //Đọc độ ẩm DHT22
  //  lumen = getLumen(LDR_PIN); 
  tempDHT = random(1,50);   //Đọc nhiệt độ DHT22
 humDHT = random(1,100);  //Đọc ánh sáng
  soilMoist = getSoilMoist();        //Đọc cảm biến độ ẩm đất
}

void printData(void)
{
  // IN thông tin ra màn hình
  Serial.print("Do am: ");
  Serial.print(humDHT);
  Serial.print(" %\t");
  Serial.print("Nhiet do: ");
  Serial.print(tempDHT);
  Serial.print(" *C\t");
  //  Serial.print("Anh sang: ");
  //  Serial.print(lumen);
  Serial.print(" \t");
  Serial.print("Do am dat: ");
  Serial.print(soilMoist);
  Serial.println(" %");
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
/****************************************************************
  Hàm đọc trạng thái bơm và kiểm tra nút nhấn
  (Nút nhấn mặc định là mức "CAO"):
****************************************************************/
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

}
/***************************************************
  Thực hiện điều khiển các bơm
****************************************************/

/***************************************************
  Hàm kiểm tra trạng thái phím bấm
****************************************************/
void turnPumpOn()
{
  pumpStatus = 1;
  aplyCmd();
  delay (TIME_PUMP_ON*1000);
  pumpStatus = 0;
  aplyCmd();
}
/***************************************************
* Bật đèn trong thời gian định sẵn
****************************************************/
void turnLampOn()
{
  lampStatus = 1;
  aplyCmd();
  delay (TIME_LAMP_ON*1000);
  lampStatus = 0;
  aplyCmd();
}
void autoControlPlantation(void)
{ 
  if (soilMoist < DRY_SOIL) 
  {
    turnPumpOn();
  }

  if (tempDHT < COLD_TEMP) 
  {
    turnLampOn();
  }
}
/***************************************************
* Bật bơm trong thời gian định sẵn
****************************************************/



void setup() {
  delay(1000);
  Serial.begin(115200);
//  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
  
  server.on("/", handleRoot);  
  
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(PUMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(LAMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(SENSORS_READ_BUTTON, INPUT_PULLUP);
  aplyCmd();
  // Khởi tạo cổng serial baud 115200

  Serial.println("HocARM NDTR Bot!");
  // Bắt đầu đọc dữ liệu
  dht.begin();
  readSensors(); // Khởi tạo đọc cảm biến
  //startTiming = millis(); // Bắt đầu đếm thời gian
  server.begin();
}

void loop() {
  server.handleClient();
  readSensors();
  printData();
  HTTPClient http;    //Declare object of class HTTPClient

  String  postData;
  //int adcvalue=analogRead(A0);  //Read Analog value of LDR
  //ADCData = String(adcvalue);   //String to interger conversion
  //
  //station = "A";
 
  //Post Data
  postData = "Nhiet_Do=" + String(tempDHT)+ "&Do_Am=" + String(humDHT) + "&Do_Am_Dat=" + String(soilMoist)+ "&Den=" + String(lampStatus) + "&Bom=" + String(pumpStatus) ;
  
  http.begin("http://192.168.100.5:8077/test1/postdemo.php");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  //Close connection
  
  //delay(5000);  //Post Data at every 5 seconds
  // Khởi tạo timer
  elapsedTime = millis() - startTiming;
       
  readLocalCmd();


// if (elapsedTime > (sampleTimingSeconds * 10000))
//  {
//   readSensors();
//   printData();
//   startTiming = millis();
//  }
  http.end();
}
