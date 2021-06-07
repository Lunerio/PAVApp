# PAVApp. Be the real owner of your smart kettle

<p align="center">
  <img src="https://raw.githubusercontent.com/Lunerio/PAVApp/main/pictures/pavapp_logo.png" alt="logo"/>
</p>

## Devices used
* SONOFF Mini DIY
* DS18B20 temperature sensor
* ft232 USB UART ttl converter
* RaspberryPi with Raspbian OS

### Device configuration
* Install the Arduino IDE.
* Copy the content of the libraries folder inside the repository into the libraries folder of the Arduino IDE.
* Open the the Arduino IDE as superuser.
* Go to File -> Preferences.
* On the following section paste this link: https://arduino.esp8266.com/stable/package_esp8266com_index.json
![pref_link](https://raw.githubusercontent.com/Lunerio/PAVApp/main/pictures/link_preferences.png)
* Go to Tools -> Board -> Boards manager.
* Search for this library and install it:
![esp_lib](https://raw.githubusercontent.com/Lunerio/PAVApp/main/pictures/esp_lib.png)
* Select the correct board on Tools -> Board -> ESP8266 boards -> Generic ESP8266 Module.
* Open the web_server_arduino.ino file from the repository folder.
* Edit the file to match the login information of your WiFi router.
![wifi_config](https://raw.githubusercontent.com/Lunerio/PAVApp/main/pictures/device_wifi_conf.png)
* Press the flash button on the SONOFF Mini DIY board and then connect it to the USB Port.
* On Tools -> Port choose the correct USB port.
* Upload the code to the device.
* Unplug and plug again the device to the USB port, without pressing the flash button. This will start the device and do the connection to the router and start the web server inside the device.

## Setting up the server
#### Everything was run on a Raspberry Pi with the Raspbian OS!

### server_set
* This script configures the server, installing necessary programs and libraries. It also changes the configuration of the server in order to set an static IP address locally, and a host name to have a connection through a domain rather than using the IP address each time.
* Modify the values with the given instructions within the script.
![server_conf](https://raw.githubusercontent.com/Lunerio/PAVApp/main/pictures/server_ip.png)
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
### page_deploy
* Edit "This file" in order to connect the page with the correct IP address of the device.
* This script will configure the needed files in order to run the web page that controls the device. It also starts the web application.
* In case you want to run the VUE application on the current computer do the following:
```
cd pavapp-web
sudo yarn install --network-timeout 600000
sudo yarn serve
```
* If you want to run the app from a remote computer run the page_deploy script like this:
```
sudo chmod +x page_deploy
./page_deploy <server_user> <server_ip>
```
It will automatically take the remote user and IP address and copy the needed files and it will run the VUE.js application. After this you can connect to the web page using the hostname of the server like this: hostname.local

### Extra configuration
In case you want to run the service when the server machine boots up, open with sudo nano add the following lines inside the /etc/rc.local file before the exit 0 line (on Raspberry Pi):
```
if find ~ -name 'pavapp-web'
then
	(cd ~/pavapp-web ; sudo yarn serve)
else
	:
fi
```
