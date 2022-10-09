
# Wireless Sensor Networks.









### compile cmds

make TARGET=sky motelist
make TARGET=sky PORT=/dev/ttyUSB0 hello-world.upload
make TARGET=sky PORT=/dev/ttyUSB0 login
make TARGET=native


### contiki in docker

docker run -it -v /pack/mounts/WirelessSensorNetworks/contiki-ng:/home/user/contiki-ng -v /pack/mounts/WirelessSensorNetworks/WSN:/home/user/WSN -v /dev/ttyUSB0:/dev/ttyUSB0 --name contiki -d contiki