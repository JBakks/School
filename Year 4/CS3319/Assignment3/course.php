<!--Programmer Name: 21 -->
<?php
    include "connecttodb.php";

    // date range feature
    echo "<form action='' method='post'>";
    echo "<h2>Course Offerings</h2>";
    echo "<label for='startYear'>Start Year:</label>";
    echo "<input type='text' name='startYear'>";
    echo "<br>";
    echo "<label for='endYear'>End Year:</label>";
    echo "<input type='text' name='endYear'>";
    echo "<br>";
    echo "<input type='submit' value='Search'>";
    echo "</form>";

    // if the button was clicked
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // get coursenum from url
        $selectedCourse = isset($_GET["courseNum"]) ? $_GET["courseNum"] : null;

        // get start year
        $startYear = isset($_POST["startYear"]) ? $_POST["startYear"] : null;
        $endYear = isset($_POST["endYear"]) ? $_POST["endYear"] : null;

        // course selected?
        if ($selectedCourse !== null) {
            // get the coures from start to end year
            if($startYear == "" && $endYear == ""){
                $courseDetailsQuery = "SELECT * FROM courseoffer WHERE whichcourse = '$selectedCourse'";
            } else {
                $courseDetailsQuery = "SELECT * FROM courseoffer WHERE whichcourse = '$selectedCourse' AND year BETWEEN '$startYear' AND '$endYear'";
            }
            $courseDetailsResult = mysqli_query($connection, $courseDetailsQuery);

        } 
    // if nothing entered
    }else {
            // get course id from url
            $selectedCourse = isset($_GET["courseNum"]) ? $_GET["courseNum"] : null;
            if ($selectedCourse !== null) {   
                $courseDetailsQuery = "SELECT * FROM courseoffer WHERE whichcourse = '$selectedCourse'";
                $courseDetailsResult = mysqli_query($connection, $courseDetailsQuery);
            }

            if (!$courseDetailsResult) {
                die("Database query failed: " . mysqli_error($connection));
            }
    }

    //  show course details
    if (mysqli_num_rows($courseDetailsResult) > 0) {
        echo "<table>";
        echo "<tr>
                <th>Course ID</th>
                <th>Number of Students</th>
                <th>Term</th>
                <th>Year</th>
              </tr>";

        while ($row = mysqli_fetch_assoc($courseDetailsResult)) {
            echo "<tr>";
            echo "<td>{$row['coid']}</td>";
            echo "<td>{$row['numstudent']}</td>";
            echo "<td>{$row['term']}</td>";
            echo "<td>{$row['year']}</td>";
            echo "</tr>";
        }

        echo "</table>";
    } else {
        echo "<p>No Course Offerings found for the selected Course ID and specified years.</p>";
    }

    // Close the database connection
    mysqli_close($connection);
?>
