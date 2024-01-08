<!--Programmer Name: 21-->

<!DOCTYPE html>
<html>
    <head>
        <title>Teaching Assistants</title>
    </head>
    <body>
        <?php
            include "connecttodb.php";
        ?>
        
        <h1>Degree Index</h1>
        
        <form action="" method="post">
            <label>Select Degree:</label>
            <select name="degree_type">
                <option value="Any">Any</option>
                <option value="Masters">Masters</option>
                <option value="PhD">PhD</option>
            </select>
            <input type="submit" value="Find!">
        </form>
        
        <?php
            include "getta.php";
        ?>        
    </body>
</html>
