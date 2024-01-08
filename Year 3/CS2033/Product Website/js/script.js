/*eslint-env browser*/
var parallax = document.getElementById("parallax");
function scroll() {
    if (window.scrollY > 3300) {
        scrollfire.style.width = "90%";
        scrollfire.style.top = "90px";
    }
    else {
        scrollfire.style.width = "50%";
        scrollfire.style.top = "200px";
    }
    parallax.style.backgroundPositionY = (window.scrollY*-0.3) + "px";
}

var nameBox = document.getElementById("name");
var number = document.getElementById("number");
var reason = document.getElementById("reason");
var productArea = document.getElementById("productarea");
var productBox = document.getElementById("productbox");
var messageBox = document.getElementById("messagearea");
var formbutton = document.getElementById("formbutton");
var nameRegex = /[a-zA-Z]/;
var productRegex = /^[B-C]{1}[1-10]{1}$/;
var numberRegex = /^\(?(\d{3})\)?[- ]?(\d{3})[- ]?(\d{4})$/;

function validate() {
    var valid = true;
    
    // Check Name
    if (nameBox.value.length >= 4 && nameRegex.test(nameBox.value)){
        nameBox.style.borderColor = "green";
    }else {
        nameBox.style.borderColor = "red";
        valid = false;
    }

    // Check Number
    if (numberRegex.test(number.value)){
        number.style.borderColor = "green";
    }else {
        number.style.borderColor = "red";
        valid = false;
    }

    // Check Product
    if (reason.selectedIndex == 2) {
        productArea.style.display = "block";
        if (productRegex.test(productBox.value)){
            productBox.style.borderColor = "green";    
        }else {
            productBox.style.borderColor = "red";
            valid = false;
        }
    }else{
        productArea.style.display = "none";   
    }

    // Check Message
    if (messageBox.value.length > 10 && messageBox.value.length < 30){
        messageBox.style.borderColor = "green";
    }else {
        messageBox.style.borderColor = "red";
        valid = false;
    }

    // Show submit button
    if (valid){
        formbutton.style.display = "block";
    }else {
        formbutton.style.display = "none";
    }
}

