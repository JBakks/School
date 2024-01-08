function displayDeal() {
    var today = new Date();
    var day = today.getDay();
    var msg = "";

    if (day == 0) { 
        msg = "20% off the classic breakfast"; 
    } else if (day == 1) { 
        msg = "Free cup of coffee with every meal"; 
    } else if (day == 2) {
        msg = "No Tax Tuesday!";
    } else if (day == 3) {
        msg = "Students get 15% off!";
    } else if (day == 4){
        msg = "Half price sweets!";
    } else if (day == 5){
        msg = "Half price drinks!";
    } else if (day == 6){
        msg = "Kids eat free!";
    }

    document.getElementById("msgBox").innerHTML = msg;
}
