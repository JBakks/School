<!--Programmer Name: 21 -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Delete TA</title>
</head>
<body>
    <h2>Delete TA</h2>
    
    // enter western id
    <form action="" method="post">
        <label>Enter TA's Western User ID:</label>
        <input type="text" name="taID" required>
        <br>
        <input type="submit" value="Delete TA">
    </form>
    <?php
        include "deletelogic.php";
    ?>
</body>
</html>