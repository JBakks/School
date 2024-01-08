<!--Programmer Name: 21 -->
<?php
include "connecttodb.php";

// form submitted?
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // get all the info to add
    $tauserid = mysqli_real_escape_string($connection, $_POST["tauserid"]);
    $firstname = mysqli_real_escape_string($connection, $_POST["firstname"]);
    $lastname = mysqli_real_escape_string($connection, $_POST["lastname"]);
    $studentnum = mysqli_real_escape_string($connection, $_POST["studentnum"]);
    $degreetype = mysqli_real_escape_string($connection, $_POST["degreetype"]);
    $image = mysqli_real_escape_string($connection, $_POST["image"]);
    $selectedCoursesLoved = isset($_POST["selected_coursesloved"]) ? $_POST["selected_coursesloved"] : [];
    $selectedCoursesHated = isset($_POST["selected_courseshated"]) ? $_POST["selected_courseshated"] : [];

    // does the id already exist
    $checkExistingQuery = "SELECT * FROM ta WHERE tauserid = '$tauserid' OR studentnum = '$studentnum'";
    $existingResult = mysqli_query($connection, $checkExistingQuery);

    if (mysqli_num_rows($existingResult) > 0) {
        echo "<p>Error: TA with the entered Western User ID or student number already exists.</p>";
    } else {
        // add ta to database
        $insertQuery = "INSERT INTO ta (tauserid, firstname, lastname, studentnum, degreetype, image)
                        VALUES ('$tauserid', '$firstname', '$lastname', '$studentnum', '$degreetype', '$image')";

        $insertResult = mysqli_query($connection, $insertQuery);
        
        // insert to love or hate
        foreach ($selectedCoursesLoved as $course) {
            $insertQuery = "INSERT INTO loves (ltauserid, lcoursenum) VALUES ('$tauserid', '$course')";
            $insertResult = mysqli_query($connection, $insertQuery);

            if (!$insertResult) {
                die("Error inserting data: " . mysqli_error($connection));
            }
        }
        
        foreach ($selectedCoursesHated as $course) {
            $insertQuery = "INSERT INTO hates (htauserid, hcoursenum) VALUES ('$tauserid', '$course')";

            $insertResult = mysqli_query($connection, $insertQuery);

            if (!$insertResult) {
                die("Error inserting data: " . mysqli_error($connection));
            }
        }

        if ($insertResult) {
            echo "<p>New TA added successfully.</p>";
        } else {
            echo "<p>Error adding new TA: " . mysqli_error($connection) . "</p>";
        }
    }
}

    // Close the database connection
    mysqli_close($connection);
?>