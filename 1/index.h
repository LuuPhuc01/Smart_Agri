char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta charset ="utf-8">

        <title>Đồ án nhiệt độ và độ ẩm dùng ESP8266</title>
 
        <style>
        @import url("https://fonts.googleapis.com/css2?family=Poppins:ital,wght@0,100;0,200;1,100;1,200&display=swap");
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}
body {
  background: linear-gradient(to right, #9fa5d5, #e8f5c8);
  height: 100vh;
}
#menu_top {
  position: relative;
  align-items: center;
  background: #3b3838;
  color: #fff;
  height: 100px;
  width: 100%;
}

#menu_top ul {
  margin: 0px;
  padding: 0px;
}
#menu_top ul li {
  list-style: none;
  float: left;
}
#menu_top ul li a {
  text-decoration: none; /*xóa gạch chân*/
  display: block;
  height: 100px;
  line-height: 100px;
  color: #fff;
  font-size: 30px;
  padding: 0px 20px 0px 20px;
  /*border: 1px solid #ccc;*/
}
#banner {
  height: auto;
  width: auto;
}

#banner img {
  object-fit: cover;
  width: 100%;
  height: 100%;
}
#main {
  margin-top: 15px;
  display: flex;
  justify-content: center;
}

.card {
  padding: 20px;
  margin: 15px;
  width: 200px;
  height: 250px;
  border-radius: 5px;
  text-align: center;
}
.Temperature {
  background: linear-gradient(45deg, #be285a 0%, #a11e4a 100%);
  color: #ffffff;
  transition: all 0.3s ease-in-out;
}
.Humidity {
  background: linear-gradient(45deg, #02d11e 0%, #117c3a 100%);
  transition: all 0.3s ease-in-out;
  color: #ffffff;
}
.Soil {
  background: linear-gradient(45deg, #3a0308 0%, #ce6c11 100%);
  color: #ffffff;
  transition: all 0.3s ease-in-out;
}
.Lamp {
  background: linear-gradient(45deg, #d1c302 0%, #da7d26 100%);
  color: #ffffff;
  transition: all 0.3s ease-in-out;
}
.Motor {
  background: linear-gradient(45deg, #0288d1 0%, #26c6da 100%);
  color: #ffffff;
  transition: all 0.3s ease-in-out;
}
.Automatic {
  background: linear-gradient(45deg, #141413 0%, #969493 100%);
  color: #ffffff;
  transition: all 0.3s ease-in-out;
}
#main .card img {
  object-fit: cover;
  width: 100%;
  height: 100%;
  object-position: center;
  margin: 0px auto;
  padding: 10px;
  width: 70px;
  height: 70px;
  border: 2px solid black;
  border-radius: 50%;
  background: #fff;
}
#main .card h2 {
  font-size: 22px;
  margin-top: 10px;
  margin-bottom: 10px;
  font-family: "poppins";
}
#main .card h1 {
  font-size: 30px;
  margin-bottom: 10px;
}
.card .button1 {
  width: 60px;
  height: 30px;
  border: 2px solid black;
  border-radius: 5px;
  background: white;
  transition: 0.5s;
  cursor: pointer;
}
.card .button1:hover {
  background: black;
  color: white;
}
#main .Automatic a {
  text-decoration: none;
  color: #fff;
  display: block;
  padding-top: 5px;
  font-size: 20px;
}

        </style>

    </head>
    <body>
        <div id = "menu_top">
            <ul>
                <li><a href="/" title ="Trang chủ" >Home</a> </li>
                <li><a href="http://192.168.1.16:8077/test1/view.php" target="_blank" title ="Data" >Data</a> </li>
            </ul>
            </div>
            <div id = "banner">
                <img src = "https://i.imgur.com/0N51VCT.png"/>
            </div>
        </div>
        <div id ="main">
            <div class ="card Temperature">
                <img src="https://i.imgur.com/byifRzR.png"/>
                <h2>Temperature</h2>
                <h1 ><span id="temp"></span>*C</h1>

            </div>
            <div class ="card Humidity">
                <img src="https://orioni.co/nmedia/png/humidity-4401.png"/>
                
                <h2>Humidity</h2>
                <h1> <span id="hum"></span>% </h1>

            </div>
            <div class ="card Soil">
                <img src="https://i.imgur.com/Q92kdIi.png"/>
                
                <h2>Soil moisture</h2>
                <h1 ><span id="soil"></span>%</h1>

            </div>
        </div>
        <div id ="main">
            <div class ="card Lamp">
                <img src="https://i.imgur.com/gRoFvxV.png"/>
                
                <h2>Lamp</h2>
                <h1 id="trangthaiD2"></h1>
                <button class ="button1" onclick="getdata('onD2')">ON</button>
                <button class ="button1" onclick="getdata('offD2')">OFF</button>

            </div>
            <div class ="card Motor">
                <img src="https://i.imgur.com/2CfgPZH.png"/>               
                <h2>Motor</h2>
                <h1 id="trangthaiD5"></h1>
                <button class ="button1" onclick="getdata('onD5')">ON</button>
                <button class ="button1" onclick="getdata('offD5')">OFF</button>

            </div>
            <div class ="card Automatic">
                <img src="https://cdn.iconscout.com/icon/premium/png-256-thumb/automatic-2355136-1964528.png"/>          
                <h2>Automatic</h2>
                <h1 id="trangthaiD1"></h1>
                <button class ="button1" onclick="getdata('onD1')">ON</button>
                <button class ="button1" onclick="getdata('offD1')">OFF</button>
                <a href="http://192.168.1.20/setting" target ="_blank" > Setting</a>
            </div>
      </div>
    </body>
    <script>
  
        //-----------Tạo đối tượng request----------------
function create_obj(){
td = navigator.appName;
if(td == "Microsoft Internet Explorer"){
  obj = new ActiveXObject("Microsoft.XMLHTTP");
}else{
  obj = new XMLHttpRequest();
}
return obj;
}
var xhttp = create_obj();
//-----------Thiết lập dữ liệu và gửi request-------
function getdata(url){
xhttp.open("GET","/"+url,true);
xhttp.onreadystatechange = process;//nhận reponse 
xhttp.send();
}
//-----------Kiểm tra response--------------------
function process(){
if(xhttp.readyState == 4 && xhttp.status == 200){
  //------Updat data sử dụng javascript----------
  ketqua = xhttp.responseText; 
  document.getElementById("reponsetext").innerHTML=ketqua;       
}
}  
  
  
  function getstatusD2D5(){
xhttp.open("GET","/getstatusD2D5",true);
xhttp.onreadystatechange = process_json;
xhttp.send();
}
//-----------Kiểm tra response-------------------------------
function process_json(){
if(xhttp.readyState == 4 && xhttp.status == 200){
  //------Update data sử dụng javascript-------------------
  var trangthaiD2D5_JSON = xhttp.responseText;
  var Obj = JSON.parse(trangthaiD2D5_JSON);
  document.getElementById("trangthaiD2").innerHTML = Obj.D2;
  document.getElementById("trangthaiD5").innerHTML = Obj.D5;
  document.getElementById("trangthaiD1").innerHTML = Obj.D1;
  document.getElementById("temp").innerHTML = Obj.temp;
  document.getElementById("hum").innerHTML = Obj.hum;
  document.getElementById("soil").innerHTML = Obj.soil;
  
}
}
//---Ham update duu lieu tu dong---
setInterval(function() {
getstatusD2D5();
}, 1000);




</script>
   
</html>
)=====";
