var UserName = "Bhargavi"
var PassWord = "1234"
var maxChances = 5
var cur_chance = 0

function authentication() {
    var cust_Name = document.getElementById("myID").value;
    var cust_Password = document.getElementById("myPassword").value;
    if(cust_Name == UserName)
    {
        if(cust_Password == PassWord)
        {
            // window.location.href = 'index.html';
            setTimeout("window.location.replace('index.html'), 0")
        }
    }
    else{
        cur_chance = cur_chance + 1
        alert("Invaid Authenticaton !! Please try again. ");
    }
    
}