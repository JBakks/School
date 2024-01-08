<!--Programmer Name: 21 -->

<?php
    include "connecttodb.php";
    //message to put at top
    $updatedMessage = "";

    // was form submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // ta selected?
        if (isset($_POST["selected_ta"])) {
            // Get ta id
            $selectedTaID = mysqli_real_escape_string($connection, $_POST["selected_ta"]);

            // Course selected?
            if (isset($_POST["selected_course"])) {
                $selectedCoID = mysqli_real_escape_string($connection, $_POST["selected_course"]);

                // Hours empty?
                if (!empty($_POST["hours"])) {
                    // Check if the entered TA is already assigned to that course
                    $checkExistingQuery = "SELECT * FROM hasworkedon WHERE tauserid = '$selectedTaID' AND coid = '$selectedCoID'";
                    $existingResult = mysqli_query($connection, $checkExistingQuery);

                    if (mysqli_num_rows($existingResult) > 0) {
                        $updatedMessage = "<p>Error: TA is already working on that Course Offering.</p>";
                    } else {
                        // Insert new work into hasworkedon
                        $hours = mysqli_real_escape_string($connection, $_POST["hours"]);
                        $insertQuery = "INSERT INTO hasworkedon (tauserid, coid, hours) VALUES ('$selectedTaID', '$selectedCoID', '$hours')";
                        $insertResult = mysqli_query($connection, $insertQuery);
                        $updatedMessage = "<p>Success: TA is now on that Course Offering.</p>";
                    }
        // Errors
                } else {
                    $updatedMessage = "Error: Please enter the number of hours.";
                }
            } else {
                $updatedMessage = "Error: Please select a CourseOffering.";
            }
        } else {
            $updatedMessage = "Error: Please select a TA.";
        }
    }

    // Get ta from database
    $result = mysqli_query($connection, "SELECT * FROM ta");
    if (!$result) {
        die("Database query failed: " . mysqli_error($connection));
    }
    echo "<h3>Teaching Assistants</h3>";

    echo "<p>$updatedMessage</p>";
    echo "<form action='' method='post'>";
    echo "<table>";
    echo "<tr>
            <th>Select</th>
            <th>TA ID</th>
            <th>First Name</th>
            <th>Last Name</th>
            <th>Student Number</th>
            <th>Degree Type</th>
          </tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        // Add a radio button for each row
        echo "<td><input type='radio' name='selected_ta' value='{$row['tauserid']}'></td>";
        echo "<td>{$row['tauserid']}</a></td>";
        echo "<td>{$row['firstname']}</td>";
        echo "<td>{$row['lastname']}</td>";
        echo "<td>{$row['studentnum']}</td>";
        echo "<td>{$row['degreetype']}</td>";
        echo "</tr>";
    }

    echo "</table>";

    echo "<h3>Courses</h3>";
    echo "<form action='' method='post'>";
    echo "<table>";
    echo "<tr>
            <th>Select</th>
            <th>Course Number</th>
            <th>Course ID</th>
          </tr>";

    $result = mysqli_query($connection, "SELECT * FROM courseoffer");
    if (!$result) {
        die("Database query failed: " . mysqli_error($connection));
    }

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        // Add a radio button for each row
        echo "<td><input type='radio' name='selected_course' value='{$row['coid']}'></td>";
        echo "<td>{$row['whichcourse']}</a></td>";
        echo "<td>{$row['coid']}</td>";

        echo "</tr>";
    }

    echo "</table>";

    echo "<label>Number of Hours:</label>";
    echo "<input type='text' name='hours'>";
    echo "<br>";
    echo "<input type='submit' name='assignta' value='Assign TA'>";
    echo "</form>";

    mysqli_free_result($result);
?>
