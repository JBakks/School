<!--Programmer Name: 21 -->
<?php
    include "connecttodb.php";

    // Get the selected TA 
    $selectedTAID = isset($_GET["taid"]) ? $_GET["taid"] : null;

    // Check if there is a ta
    if ($selectedTAID !== null) {
        // Query to fetch TA details
        $taDetailsQuery = "SELECT * FROM ta WHERE tauserid = '$selectedTAID'";
        $taDetailsResult = mysqli_query($connection, $taDetailsQuery);

        if (!$taDetailsResult) {
            die("Database query failed: " . mysqli_error($connection));
        }

        if ($ta = mysqli_fetch_assoc($taDetailsResult)) {
            // Display details
            echo "<h2>TA Details</h2>";
            if($ta['image'] == null){
                echo "<img src='https://i.pinimg.com/originals/b4/6c/70/b46c7045f5a7d5e5d72d8128e6a9510a.jpg' alt='TA Image' style='width: 200px; height: 200px;'>";
            }else{
                echo "<img src='{$ta['image']}' alt='TA Image' style='width: 200px; height: 200px;'>";
            }
            echo "<p>TA ID: {$ta['tauserid']}</p>";
            echo "<p>First Name: {$ta['firstname']}</p>";
            echo "<p>Last Name: {$ta['lastname']}</p>";
            echo "<p>Student Number: {$ta['studentnum']}</p>";
            echo "<p>Degree Type: {$ta['degreetype']}</p>";
            
            // Query for loved
            $coursesLovedQuery = "SELECT * FROM loves WHERE ltauserid = '$selectedTAID'";
            $coursesLovedResult = mysqli_query($connection, $coursesLovedQuery);

            // Query for hated
            $coursesHatedQuery = "SELECT * FROM hates WHERE htauserid = '$selectedTAID'";
            $coursesHatedResult = mysqli_query($connection, $coursesHatedQuery);
            
            // List the courses loved by ta
            echo "<h3>Courses Loved by the TA</h3>";
            if (mysqli_num_rows($coursesLovedResult) > 0) {
                echo "<ul>";
                while ($course = mysqli_fetch_assoc($coursesLovedResult)) {
                    echo "<li>{$course['lcoursenum']}</li>";
                }
                echo "</ul>";
            } else {
                echo "<p>This TA has not picked courses that they love.</p>";
            }
            
            // LIst the cousre hated by the ta
            echo "<h3>Courses Hated by the TA</h3>";
            if (mysqli_num_rows($coursesHatedResult) > 0) {
                echo "<ul>";
                while ($course = mysqli_fetch_assoc($coursesHatedResult)) {
                    echo "<li>{$course['hcoursenum']}</li>";
                }
                echo "</ul>";
            } else {
                echo "<p>This TA has not picked courses that they hate.</p>";
            }

            
            mysqli_free_result($taDetailsResult);
            mysqli_free_result($coursesLovedResult);
            mysqli_free_result($coursesHatedResult);
        } else {
            echo "<p>No TA found with the selected ID.</p>";
        }
    } else {
        echo "<p>No TA ID provided.</p>";
    }

    // Close the database connection
    mysqli_close($connection);
?>
