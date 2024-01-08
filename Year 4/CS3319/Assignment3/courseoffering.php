<!--Programmer Name: 21 -->
<?php
    include "connecttodb.php";

    // Get the selected course id form url
    $selectedCOID = isset($_GET["coid"]) ? $_GET["coid"] : null;

    // Course selected?
    if ($selectedCOID !== null) {
        // Get details
        $coidDetailsQuery = "SELECT * FROM courseoffer, course WHERE coid = '$selectedCOID' AND coursenum = whichcourse";
        $coidDetailsResult = mysqli_query($connection, $coidDetailsQuery);

        if (!$coidDetailsResult) {
            die("Database query failed: " . mysqli_error($connection));
        }

        // Display details
        echo "<h2>Course Offerings</h2>";
        echo "<table>";
        echo "<tr>
            <th>Course Number</th>
            <th>Course Name</th>
        </tr>";

        while ($row = mysqli_fetch_assoc($coidDetailsResult)) {
            echo "<tr>";
            echo "<td>{$row['whichcourse']}</td>";
            echo "<td>{$row['coursename']}</td>";
            echo "</tr>";

            // Get tas
            $taDetailsQuery = "SELECT ta.firstname, ta.lastname, ta.tauserid FROM hasworkedon JOIN ta ON hasworkedon.tauserid = ta.tauserid WHERE hasworkedon.coid = '$selectedCOID'";
            $taDetailsResult = mysqli_query($connection, $taDetailsQuery);

            if (!$taDetailsResult) {
                die("Database query failed: " . mysqli_error($connection));
            }

            // ta detaiusl
            echo "<tr>
                <th>TA First Name</th>
                <th>TA Last Name</th>
                <th>TA ID</th>
            </tr>";

            while ($taRow = mysqli_fetch_assoc($taDetailsResult)) {
                echo "<tr>";
                echo "<td>{$taRow['firstname']}</td>";
                echo "<td>{$taRow['lastname']}</td>";
                echo "<td>{$taRow['tauserid']}</td>";
                echo "</tr>";
            }

            mysqli_free_result($taDetailsResult);
        }

        echo "</table>";

        mysqli_free_result($coidDetailsResult);
    } else {
        echo "<p>No COID provided.</p>";
    }

    // Close the database connection
    mysqli_close($connection);
?>
