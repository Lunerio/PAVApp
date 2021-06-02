# PAVApp. Be the real owner of your smart kettle

## Devices used
* SONOFF Mini DIY
* DS18B20 temperature sensor
* ft232 USB UART ttl converter
* RaspberryPi with Raspbian OS

### Device configuration
* Install the Arduino IDE.
* Copy the content of the libraries folder inside the repository into the libraries folder of the Arduino IDE.
* Open the the Arduino IDE as superuser.
* Go to Tools -> Board -> Boards manager.
* Search for this library and install it: (picture of the library)
* Select the correct board on Tools -> Board -> ESP8266 boards -> Generic ESP8266 Module.
* Open the web_server_arduino.ino file from the repository folder.
* Edit the file to match the login information of your WiFi router. (picture here)
* Press the flash button on the SONOFF Mini DIY board and then connect it to the USB Port.
* On Tools -> Port choose the correct USB port.
* Upload the code to the device.
* Unplug and plug again the device to the USB port, without pressing the flash button. This will start the device and do the connection to the router and start the web server inside the device.

## Setting up the server
#### Everything was run on a Raspberry Pi with the Raspbian OS!

### server_set
* This script configures the server, installing necessary programs and libraries. It also changes the configuration of the server in order to set an static IP address locally, and a host name to have a connection through a domain rather than using the IP address each time.
* Modify the values with the given instructions within the script. (picture here)
* If you want to run the server locally follow these instructions after editing the file:
```
sudo chmod +x server_set
./server_set
```

* If you want to create the server in another machine in your local network do the following, where user is the remote machine user, and ip is the remote machine ip address:
```
sudo chmod+x server_set
scp ./server_set user@ip:~
ssh user@ip '~/server_set'
```

## Deploying the web page
### web_deploy
* This script will configure the needed files in order to run the web page that controls the device. It also starts the web application.
* Edit "This file" in order to connect the page with the correct IP address of the device.
