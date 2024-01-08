<!--Programmer Name: 21 -->
<?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        $order = isset($_POST["order"]) ? $_POST["order"] : "tauserid";
        $orderDirection = isset($_POST["order_direction"]) ? $_POST["order_direction"] : "asc";
        $degreeType = isset($_POST["degree_type"]) ? $_POST["degree_type"] : "Any";

        // with sort
        if($degreeType == "Any"){
            $query = "SELECT * FROM ta ORDER BY $order $orderDirection";
        }else{
            $query = "SELECT * FROM ta WHERE degreetype = '$degreeType' ORDER BY $order $orderDirection";

        }
    } else {
        // without sorting
        $query = "SELECT * FROM ta";
    }

    $result = mysqli_query($connection, $query);
    if (!$result) {
        die("databases query failed: " . mysqli_error($connection));
    }
    
    //display all ta info
    echo "<table>";
    echo "<tr>
            <th>TA ID</th>
            <th>First Name</th>
            <th>Last Name</th>
            <th>Student Number</th>
            <th>Degree Type</th>
          </tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td><a href='tacourses.php?taid={$row['tauserid']}'>{$row['tauserid']}</a></td>";
        echo "<td>{$row['firstname']}</td>";
        echo "<td>{$row['lastname']}</td>";
        echo "<td>{$row['studentnum']}</td>";
        echo "<td>{$row['degreetype']}</td>";
        echo "</tr>";
    }

    echo "</table>";
    mysqli_free_result($result);
    ?>
