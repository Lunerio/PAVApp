var butt = document.getElementById('quickstart');

butt.addEventListener("click", function() {
    if (butt.classList.contains('btn-outline-secondary')) {
        // Send post request to turn off kettle
        butt.className = 'btn btn-success';
        butt.innerHTML = "On";
        console.log('it works');
    }
    else {
        // Turn kettle off
        butt.className = 'btn btn-outline-secondary';
        butt.innerHTML = "Off";
    };
});
