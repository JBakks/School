<!--Programmer Name: 21 -->
<?php
    $query = "SELECT * FROM courseoffer";

    $result = mysqli_query($connection, $query);
    if (!$result) {
        die("databases query failed: " . mysqli_error($connection));
    }
    
    //show course offerings, same logic as all my other get...php files
    echo "<table>";
    echo "<tr>
            <th>Course Offerings</th>
            <th>Number of Students</th>
            <th>Term</th>
            <th>Year</th>
            <th>Which Course</th>
          </tr>";

    while ($row = mysqli_fetch_assoc($result)) {
        echo "<tr>";
        echo "<td><a href='courseoffering.php?coid={$row['coid']}'>{$row['coid']}</a></td>";
        echo "<td>{$row['numstudent']}</td>";
        echo "<td>{$row['term']}</td>";
        echo "<td>{$row['year']}</td>";
        echo "<td>{$row['whichcourse']}</td>";
        echo "</tr>";
    }

    echo "</table>";
    mysqli_free_result($result);
    ?>
