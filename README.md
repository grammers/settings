# settings 
ROS node for relay controlled features and similar.
In the project [PermoCar](https://github.com/Trobolit/PermoCar).
Connected features are: relay breaking power to engines and warning light on/off.

## Subscribe
* Topic joy, sensor_msgs/Joy (controller input).
* Topic controll_panel, std_msgs/Int32MultiArray (control panel commands).

## Publiching
* Topic relay_control, std_msgs/Int32MultiArray (relay setting command).

## Mapping
Relay_control is a array with indexing mapped:
0 -> engine,
1 -> engine,
2 -> warning light.

Controll_panel is an array with indexing mapped: 
0 -> engines, 
1-> warning light.

Joys relevant buttons are:
0 (A) -> engine,
3 (Y) -> warning light.
