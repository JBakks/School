<!--Programmer Name: 21 -->

<!DOCTYPE html>
<html>
    <head>
        <title>Teaching Assistants</title>
    </head>
    <body>
        <?php
            include "connecttodb.php";
        ?>
        
        <h1>Teaching Assistants Index</h1>
        
<!--        Buttons for sorting-->
        <form action="" method="post">
            <label>Order by:</label>
            <input type="radio" name="order" value="lastname" checked> Last Name
            <input type="radio" name="order" value="degreetype"> Degree Type
            <br>
            <label>Order direction:</label>
            <input type="radio" name="order_direction" value="asc" checked> Ascending
            <input type="radio" name="order_direction" value="desc"> Descending
            <br>
            <input type="submit" value="Sort!">
        </form>
        
        <?php
            include "getta.php";
        ?>        
    </body>
</html>
