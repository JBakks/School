<!--Programmer Name: 21 -->

<?php
    include "connecttodb.php";
    
    // show new url at the end of updated
    $updatedURL = ""; 

    // form submitted?
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // ta selected?
        if (isset($_POST["selected_ta"])) {
            // get the id
            $selectedTaID = mysqli_real_escape_string($connection, $_POST["selected_ta"]);

            // is there aurl
            if (isset($_POST["new_url"])) {
                // if yes get it
                $newURL = mysqli_real_escape_string($connection, $_POST["new_url"]);

                // update
                $updateQuery = "UPDATE ta SET image = '$newURL' WHERE tauserid = '$selectedTaID'";
                $updateResult = mysqli_query($connection, $updateQuery);

                if ($updateResult) {
                    $updatedURL = "URL updated successfully: $newURL";
                } else {
                    $updatedURL = "Error updating URL: " . mysqli_error($connection);
                }
            } else {
                $updatedURL = "Error: Please provide a new URL.";
            }
        } else {
            $updatedURL = "Error: Please select a TA.";
        }
    }

    // get tas from datbase
    $result = mysqli_query($connection, "SELECT * FROM ta");
    if (!$result) {
        die("Database query failed: " . mysqli_error($connection));
    }

    echo "<form action='' method='post'>";
    echo "<table>";
    echo "<tr>
            <th>Select</th>
            <th>TA ID</th>
            <th>First Name</th>
            <th>Last Name</th>
            <th>Student Number</th>
            <th>Degree Type</th>
            <th>URL</th>
          </tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td><input type='radio' name='selected_ta' value='{$row['tauserid']}'></td>";
        echo "<td>{$row['tauserid']}</a></td>";
        echo "<td>{$row['firstname']}</td>";
        echo "<td>{$row['lastname']}</td>";
        echo "<td>{$row['studentnum']}</td>";
        echo "<td>{$row['degreetype']}</td>";
        echo "<td>{$row['image']}</td>";
        echo "</tr>";
    }

    echo "</table>";
    echo "<label>New URL:</label>";
    echo "<input type='text' name='new_url'>";
    echo "<br>";
    echo "<input type='submit' name='update_url' value='Update URL'>";
    echo "</form>";

    // Display the updated URL
    echo "<p>$updatedURL</p>";

    mysqli_free_result($result);
?>
