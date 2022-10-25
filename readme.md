
# Wireless Sensor Networks.









### compile cmds

make TARGET=sky motelist
make TARGET=sky PORT=/dev/ttyUSB0 hello-world.upload
make TARGET=sky PORT=/dev/ttyUSB0 login
make TARGET=native


### contiki in docker

docker run -it -v /pack/mounts/WirelessSensorNetworks/contiki-ng:/home/user/contiki-ng -v /pack/mounts/WirelessSensorNetworks/WSN:/home/user/WSN -v /dev/ttyUSB0:/dev/ttyUSB0 --name contiki -d contiki


alias contiker="docker run --privileged --sysctl net.ipv6.conf.all.disable_ipv6=0 --mount type=bind,source=/pack/mounts/WirelessSensorNetworks/contiki-ng,destination=/home/user/contiki-ng -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix -v /pack/mounts/WirelessSensorNetworks/WSN:/home/user/WSN -v /dev/bus/usb:/dev/bus/usb -ti contiker/contiki-ng"



./msp430-bsl-linux --telosb -c /dev/ttyUSB0 -e
./msp430-bsl-linux --telosb -c /dev/ttyUSB0 -I -p ../../../contiki-ng/examples/dev/leds/leds-example.ihex
./msp430-bsl-linux --telosb -c /dev/ttyUSB0 -r


 make TARGET=sky PORT=/dev/ttyUSB0 main.upload && ./program_telosb.sh main.ihex && make TARGET=sky PORT=/dev/ttyUSB0 login