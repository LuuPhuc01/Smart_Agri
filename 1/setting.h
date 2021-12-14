char MAIN_page1[] PROGMEM = R"=====(
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
            <form action="/setup1" method="post">
            <h2>Đèn bật khi Nhiệt độ thấp hơn</h2>
            <input type="number"  pattern="\d*" name="COLD_TEMP1">
            <h2>tắt khi Nhiệt độ cao hơn</h2>
            <input type="text"  name="HOT_TEMP1"><br><br>

            <h2 for="fname">Máy bơm bật khi Độ ẩm đất thấp hơn</h2>
            <input type="text"  name="DRY_SOIL1">
            <h2 for="lname"> tắt khi Độ ẩm đất cao hơn</h2>
            <input type="text"  name="WET_SOIL1"><br><br>
            <input type="submit" value="Submit">

          </form>
        </div>

      </div>
    </body>
   
</html>
)=====";
