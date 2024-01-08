<!--Programmer Name: 21 -->
<?php
    include "connecttodb.php";
    // get everything from courses
    $query = "SELECT * FROM course";

    $result = mysqli_query($connection, $query);
    if (!$result) {
        die("databases query failed: " . mysqli_error($connection));
    }
    
    // able displauying the data
    echo "<table>";
    echo "<tr>
            <th>Course Number</th>
            <th>Course Name</th>
            <th>Level</th>
            <th>Year Created</th>
          </tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td><a href='course.php?courseNum={$row['coursenum']}'>{$row['coursenum']}</a></td>";
        echo "<td>{$row['coursename']}</td>";
        echo "<td>{$row['level']}</td>";
        echo "<td>{$row['year']}</td>";
        echo "</tr>";
    }

    echo "</table>";
    mysqli_free_result($result);
?>
