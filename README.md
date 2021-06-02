# PAVApp. Be the real owner of your smart kettle

## Setting up the server

### server_set
* This script configures the server, installing necessary programs and libraries.
* It also changes the configuration of the server in order to set an static IP address locally, and a host name to have a connection through a domain rather than using the IP address each time.
* Modify the values with the given instructions within the script.
* If you want to run the server locally follow this instructions after editing the file:
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
