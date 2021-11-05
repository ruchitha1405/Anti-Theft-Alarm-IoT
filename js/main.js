function pageRedirect() {
    //window.location.href = 'login.html';
    setTimeout("window.location.href = 'login.html'", 0);
}

var video = document.getElementById("myVideo");
var btn = document.getElementById("myBtn");

function myFunction() {
    if (video.paused) {
        video.play();
        btn.innerHTML = "Pause";
    } else {
        video.pause();
        btn.innerHTML = "Play";
    }
}