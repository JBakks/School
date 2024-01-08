<!--Programmer Name: 21 -->
<?php
    include "connecttodb.php";

    // get ta from url
    $selectedTAID = isset($_GET["taid"]) ? $_GET["taid"] : null;

    // ta selected?
    if ($selectedTAID !== null) {
        // get ta details
        $taDetailsQuery = "SELECT *, courseoffer.year AS courseofferyear FROM hasworkedon, courseoffer, course WHERE tauserid = '$selectedTAID' AND hasworkedon.coid = courseoffer.coid AND courseoffer.whichcourse = course.coursenum";
        
        $taDetailsResult = mysqli_query($connection, $taDetailsQuery);

        if (!$taDetailsResult) {
            die("Database query failed: " . mysqli_error($connection));
        }

        // show details
        echo "<h2>Courses</h2>";

        echo "<table>";
        echo "<tr>
        <th>Course Number</th>
        <th>Course Name</th>
        <th>Term</th>
        <th>Year</th>
        <th>Hours</th>
        <th>Liked?</th>
        </tr>";

        //  table
        while ($row = mysqli_fetch_assoc($taDetailsResult)) {
            echo "<tr>";
            echo "<td>{$row['coursenum']}</td>";
            echo "<td>{$row['coursename']}</td>";
            echo "<td>{$row['term']}</td>";
            echo "<td>{$row['courseofferyear']}</td>";
            echo "<td>{$row['hours']}</td>";
            // check for love hate
            $tauserid = $row['tauserid'];
            $coursenum = $row['coursenum'];
            
            $checkLovesQuery = "SELECT * FROM loves WHERE ltauserid = '$tauserid' AND lcoursenum = '$coursenum'";
            $checkLovesResult = mysqli_query($connection, $checkLovesQuery);
            
            $checkHatesQuery = "SELECT * FROM hates WHERE htauserid = '$tauserid' AND hcoursenum = '$coursenum'";
            $checkHatesResult = mysqli_query($connection, $checkHatesQuery);

            if ($checkLovesResult && mysqli_num_rows($checkLovesResult) > 0) {
                // happy face if loved
                echo "<td>😊</td>";
            } else if ($checkHatesResult && mysqli_num_rows($checkHatesResult) > 0) {
                // sad face if hated
                echo "<td>😢</td>";
            }else{
                // blank for idk
                echo "<td>😐</td>";
            }
            echo "</tr>";
        }

        echo "</table>";
            
    } else {
        echo "<p>No TA ID provided.</p>";
    }

    // Close the database connection
    mysqli_close($connection);
?>
