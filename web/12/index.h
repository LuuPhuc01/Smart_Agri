String MAIN_page = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <meta charset ="utf-8">

        <title>Đồ án nhiệt độ và độ ẩm dùng ESP8266</title>
        <style>
body {
  
  background-size: 100%;
  margin: 0px auto;
  width: 1000px;
}
#menu_top {
  background: #3b3838;
  color: #fff;
  height: 100px;
  width: 1000px;
}
#main {
    position: absolute;
  margin: 0px;
  padding: 0px;
  width: 1000px;
  height: 1000px;
}
#main #main_left {
  min-height: 1000px;
  width: 1000px;
  float: left;
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
  width: 1000px;
}

#banner img {
  width: 1000px;
}

#main #main_left ul {
  margin: 0px;
  padding: 0px;
}
#main #main_left ul li {
  font-family: "Courier New", Courier, monospace;
  list-style: none;
  clear: left;
  color: rgb(0, 0, 0);

  float: left;
  margin-bottom: 20px;
}
#main #main_left ul li img {
  float: left;
  margin-right: 20px;
}
#main #main_left ul li h2 {
  float: left;
  font-size: 40px;
  font-weight: 900;
  letter-spacing: 0.1em;
} 
#main #main_left ul li h3 .button1 {
  display: inline-block;
  border-radius: 4px;
  background-color: #f4511e;
  border: none;
  color: #ffffff;
  text-align: center;
  padding: 20px;
  width: 200px;
  transition: all 0.5s;
  cursor: pointer;
  margin: 5px;
  position: absolute;
  right: 150px;
  width: 100px;
  font-size: 15px;
  height: 50px;
  padding: 10px;
  box-shadow: 0 8px 16px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
}
#main #main_left ul li h3 .button2 {
  display: inline-block;
  border-radius: 4px;
  background-color: yellow;
  border: none;
  color: #000;
  text-align: center;
  padding: 20px;
  width: 200px;
  transition: all 0.5s;
  cursor: pointer;
  margin: 5px;
  position: absolute;
  right: 45px;
  width: 100px;
  height: 50px;
  padding: 10px;
  box-shadow: 0 8px 16px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
} 
        </style>
    </head>
    <body>
        <div id = "menu_top">
        <ul>
            <li><a href="#" title ="Trang chủ" >Trang chủ</a> </li>
            <li><a href="http://192.168.100.5:8077/test1/view.php" target="_blank" title ="Data" >Data</a> </li>
        </ul>
        </div>
        <div id = "banner">
            <img src= "https://i.imgur.com/0N51VCT.png"/>
        </div>

        <div id = "main">
        <div id="main_left">
            <ul>
                <li>
                    <h1></h1>
                </li>
                <li>
                    <img src="https://i.imgur.com/byifRzR.png" width="100" height="100"/>
                    <h2>Nhiệt độ:@@temp@@ </h2>
                </li>
                <li>
                    <img src="https://i.imgur.com/r6O9bzn.png"width="100" height="100"/>
                    <h2>Độ ẩm không khí:@@hum@@ </h2>
                </li>
                <li>
                    <img src="https://i.imgur.com/Q92kdIi.png"width="100" height="100"/>
                    <h2>Độ ẩm đất: @@soil@@</h2>

                </li>
                <li>
                    <img src="https://i.imgur.com/gRoFvxV.png"width="100" height="100"/>
                    <h2>Đèn: </h2>
                                        <h3 >
                        <span >
                            <button type="button" class = "button1">Bật</button>
                        </span>
                        <span>
                            <button type="button" class = "button2" >Tắt</button>
                        </span>
                    </h3>
                </li>
                <li>
                    <img src="https://i.imgur.com/2CfgPZH.png"width="100" height="100"/>
                    <h2>Máy bơm: </h2>
                    <h3 >
                        <span >
                            <button type="button" class = "button1">Bật</button>
                        </span>
                        <span>
                            <button type="button" class = "button2" >Tắt</button>
                        </span>
                    </h3>
                </li>
            </ul >
            </div>
            </div>

    
    </body>

</html>
)=====";
