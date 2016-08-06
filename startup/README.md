
# Running Code on Boot Up

We use `systemd` to start our Node.js server and processing scripts when the Raspberry Bi boots up.

##Setting Up systemd:
To run the Node.js and Processing services on startup, `cd` into the `shrumen-lumen/startup` directory and run the following the commands in Terminal:

```
systemctl enable startup-node.service
systemctl enable pixelpusher-node.service
```

To test out new changes, you can start the services without rebooting by using `systemctl start foobar.service`. Once changes are made to these scripts, run `systemctl reenable <service>` to register the changes for the next reboot.

##Setting Up Headless Desktop
In order to run Processing scripts without a display, you need to setup a Headless Desktop for the Raspberry Pi.

To enable "headless" mode, run the following to install a virtual frame buffer.

```
sudo apt-get install xvfb libxrender1 libxtst6 libxi6
```

## References

+ [systemd: Unit Dependecies and order](https://fedoramagazine.org/systemd-unit-dependencies-and-order/)
+ [Running without a Display](https://github.com/processing/processing/wiki/Running-without-a-Display)
+ [Running an exported Processing 3 sketch on a headless Raspberry Pi](https://nocduro.ca/2016/01/06/running-an-exported-processing-3-sketch-on-a-headless-raspberry-pi/)

