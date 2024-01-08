<!--Programmer Name: 21 -->
<?php
include "connecttodb.php";

// had some weird thing where it would show error on first opening so this stops it
$confirmedDelete = false;

// was form submited
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // weird bug fix
    if (isset($_POST['confirmed_delete'])) {
        $confirmedTaID = mysqli_real_escape_string($connection, $_POST['confirmed_taID']);
        $confirmedDelete = true;

        // ta exist?
        $checkQuery = "SELECT * FROM ta WHERE tauserid = '$confirmedTaID'";
        $checkResult = mysqli_query($connection, $checkQuery);

        if (mysqli_num_rows($checkResult) > 0) {
            // DELETE
            $deleteQuery = "DELETE FROM ta WHERE tauserid = '$confirmedTaID'";
            $deleteResult = mysqli_query($connection, $deleteQuery);

            if ($deleteResult) {
                echo "TA with ID $confirmedTaID has been deleted successfully.";
            } else {
                echo "Error deleting TA: " . mysqli_error($connection);
            }
        } else {
            echo "Error: TA with ID $confirmedTaID no longer exists.";
        }
    } elseif (isset($_POST["taID"])) {
        // taid real?
        $taID = mysqli_real_escape_string($connection, $_POST["taID"]);

        // ta exist?
        $checkQuery = "SELECT * FROM ta WHERE tauserid = '$taID'";
        $checkResult = mysqli_query($connection, $checkQuery);

        if (mysqli_num_rows($checkResult) > 0) {
            // assigned to course offering if so NO
            $checkAssignmentQuery = "SELECT * FROM hasworkedon WHERE tauserid = '$taID'";
            $checkAssignmentResult = mysqli_query($connection, $checkAssignmentQuery);

            if (mysqli_num_rows($checkAssignmentResult) > 0) {
                echo "Cannot delete this TA. The TA is assigned to a course offering.";
            } else {
                // show messages
                echo "Are you sure you want to delete this TA with ID: $taID?<br>";
                echo "<form action='' method='post'>";
                echo "<input type='hidden' name='confirmed_taID' value='$taID'>";
                echo "<input type='submit' name='confirmed_delete' value='Yes'>";
                echo "<input type='submit' name='cancel_delete' value='No'>";
                echo "</form>";
            }
        } else {
            echo "Error: TA with ID $taID does not exist.";
        }
    } else {
        echo "Error: 'taID' key is not set in the form submission.";
    }
}
?>
