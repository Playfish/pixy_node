# pixy_node

This ROS package is forked on [erlerobot](https://github.com/erlerobot/erle_pixy).

## Compile

Add this folder to catkin_ws/src and the compile the code:
```
cd <your catkin_worspace>
catkin_make
```

To do this copy the 'pixy.rules' file to '/etc/udev/rules.d'

sudo cp pixy.rules /etc/udev/rules.d/

## Run


Whit this component you can see the image from Pixy Cam.
```
roslaunch pixy_node pixy_usb.launch
```


