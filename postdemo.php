<?php
//Creates new record as per request
    //Connect to database
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "SmartAgi";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Database Connection failed: " . $conn->connect_error);
    }

    //Get current date and time
    date_default_timezone_set('Asia/Kolkata');
    $d = date("Y-m-d");
    //echo " Date:".$d."<BR>";
    $t = date("H:i:s");

    if(!empty($_POST['Nhiet_Do']) && !empty($_POST['Do_Am'])&& !empty($_POST['Do_Am_Dat']))
    {
    	$Nhiet_Do = $_POST['Nhiet_Do'];
    	$Do_Am = $_POST['Do_Am'];
		$Do_Am_Dat = $_POST['Do_Am_Dat'];
		$Den = $_POST['Den'];
		$Bom = $_POST['Bom'];
	    $sql = "INSERT INTO data1 ( Nhiet_Do, Do_Am,Do_Am_Dat,Den, Bom)
		
		VALUES ( '".$Nhiet_Do."','".$Do_Am."', '".$Do_Am_Dat."', '".$Den."', '".$Bom."')";

		if ($conn->query($sql) === TRUE) {
		    echo "OK";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


	$conn->close();
?>