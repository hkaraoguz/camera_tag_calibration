# camera_tag_calibration

This ros package publishes the camera transformation given a tag. The tag should be visible at the beginning, but it can be covered after the nodes start publishing the tf.

*/calibration/robot_calib.txt* contains the calibration of the marker w.r.t. the robot base.

### usage:

roslaunch camera_tag_calibration tf_publish.launch

### what does it do:

It publishes the necessary tfs to have a transformation from the world to the kinect. There is no need to calibrate the camera, which can be moved when needed, as long as the tag is kept in the same position.

### requires:

apriltag_ros: [https://github.com/RIVeR-Lab/apriltags_ros](https://github.com/RIVeR-Lab/apriltags_ros)
iai_kinect2: [https://github.com/code-iai/iai_kinect2](https://github.com/code-iai/iai_kinect2)
