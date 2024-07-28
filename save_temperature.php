<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "iot_data";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['temperature'])) {
    $temperature = $_POST['temperature'];

    // Prepare and bind
    $stmt = $conn->prepare("INSERT INTO temperature_readings (temperature) VALUES (?)");
    $stmt->bind_param("d", $temperature);

    if ($stmt->execute()) {
        echo "Temperature data saved successfully!";
    } else {
        echo "Error: " . $stmt->error;
    }

    $stmt->close();
} else {
    echo "Invalid request!";
}

$conn->close();
?>
