<!--Programmer Name: 21 -->
<?php
 
    // get courses for the dropdown
    $coursesQuery = "SELECT * FROM course";
    $coursesResult = mysqli_query($connection, $coursesQuery);

    // was successful?
    if (!$coursesResult) {
        die("Error fetching courses: " . mysqli_error($connection));
    }
?>