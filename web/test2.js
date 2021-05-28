const butt = $("#flexSwitchCheckChecked");
butt.click(function () {
    if (butt.is(":checked")) {
        // Send post request to turn off kettle
        console.log("it's on");
    }
    else {
        // Turn kettle off
        console.log("it's off");
    };
});
