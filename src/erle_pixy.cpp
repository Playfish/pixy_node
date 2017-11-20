#include "ros/ros.h"

#include <sensor_msgs/fill_image.h>
#include <image_transport/image_transport.h>

#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <boost/thread.hpp>

#include "pixycam.h"


int main(int argc, char **argv)
{

    ros::init(argc, argv, "image_raw");

    ros::NodeHandle n;
    ros::NodeHandle private_hn_("~");
    std::string frame_id;
    ros::Rate loop_rate(50.0);
    image_transport::Publisher image_pub;

    image_transport::ImageTransport it(n);
    image_pub = it.advertise("image_raw", 1);

    sensor_msgs::Image img_;

    PixyCam cam;
    boost::thread workerThread(&PixyCam::run, &cam);
    private_hn_.param<std::string>(std::string("frame_id"), frame_id, std::string("pixy_frame"));

//    cam.run();

    int count = 0;
    while (ros::ok()){

        cv::Mat frame = cam.getImage();
        fillImage(img_, "bgr8", frame.rows, frame.cols, frame.channels() * frame.cols, frame.data);
        img_.header.seq = count;
        img_.header.stamp = ros::Time::now();
        img_.header.frame_id = frame_id;
        image_pub.publish(img_);
        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }

    return 0;
}
