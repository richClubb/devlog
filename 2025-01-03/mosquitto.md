# Mosquitto Notes

## Server Config

It's necessary to put the `listener` line in to get data from outside the computer.

```
# Place your local configuration in /etc/mosquitto/conf.d/
#
# A full description of the configuration file is at
# /usr/share/doc/mosquitto/examples/mosquitto.conf.example

#pid_file /run/mosquitto/mosquitto.pid

persistence true
persistence_location /var/lib/mosquitto/

log_dest file /var/log/mosquitto/mosquitto.log

include_dir /etc/mosquitto/conf.d

allow_anonymous true

listener 1883 0.0.0.0
```

## Client

```
mosquitto_sub -v -p 1883 -h 192.168.1.91 -t '#'
```

outputs
```
study/temperature 23.43
study/humidity 40.31
```