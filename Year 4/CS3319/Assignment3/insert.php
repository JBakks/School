<!--Programmer Name: 21 -->

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Insert New TA</title>
</head>
<body>
    <?php
        include "connecttodb.php";
    ?>
    <h2>Insert New TA</h2>
    
<!--    insert-->
    <form action="" method="post">
        <label>Western User ID:</label>
        <input type="text" name="tauserid" required>
        <br>
        <label>First Name:</label>
        <input type="text" name="firstname" required>
        <br>
        <label>Last Name:</label>
        <input type="text" name="lastname" required>
        <br>
        <label>Student Number:</label>
        <input type="text" name="studentnum" required>
        <br>
        <label>Degree Type:</label>
        <input type="text" name="degreetype" required>
        <br>
        <label>Image URL:</label>
        <input type="text" name="image">
        <br>
        
        <h2>Courses Loved:</h2>
        <?php
            include "getcourses.php";

            while ($course = mysqli_fetch_assoc($coursesResult)) {
                echo "<label><input type='checkbox' name='selected_coursesloved[]' value='{$course['coursenum']}'> {$course['coursenum']}</label><br>";
            }
            mysqli_free_result($coursesResult);
        ?>
        <br>

        <h2>Courses Hated:</h2>
        <?php
            include "getcourses.php";

            while ($course = mysqli_fetch_assoc($coursesResult)) {
                echo "<label><input type='checkbox' name='selected_courseshated[]' value='{$course['coursenum']}'> {$course['coursenum']}</label><br>";
            }
            mysqli_free_result($coursesResult);
        ?>
        <br>

        <input type="submit" value="Insert TA">
    
    </form>
    
    <?php
        include "insertlogic.php";
    ?>
    
</body>
</html>
