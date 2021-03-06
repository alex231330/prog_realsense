
#include <librealsense2/rs.hpp> 
#include <opencv2/opencv.hpp>   

using namespace cv;

int main(int argc, char* argv[]) try
{
    rs2::colorizer color_map;
    rs2::pipeline pipe;
    pipe.start();
    const auto window_name = "Display Image";
    
    namedWindow(window_name, WINDOW_AUTOSIZE);

    while (waitKey(1) < 0 && cvGetWindowHandle(window_name))
    {
        rs2::frameset data = pipe.wait_for_frames();
        rs2::frame depth = data.get_depth_frame().apply_filter(color_map);
        rs2::frame color = data.get_color_frame();

        const int w = depth.as<rs2::video_frame>().get_width();
        const int h = depth.as<rs2::video_frame>().get_height();

        const int cw = color.as<rs2::video_frame>().get_width();
        const int ch = color.as<rs2::video_frame>().get_height();

        Mat image(Size(w, h), CV_8UC3, (void*)depth.get_data(), Mat::AUTO_STEP);
        Mat color_image(Size(cw, ch), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
        cvtColor(color_image, color_image, CV_RGB2BGR);

        if (std::string(argv[1]) == "0")
        {
            imshow(window_name, image);
        }else if (std::string(argv[1]) == "1")
        {
            imshow(window_name, color_image);
        }
    }
    return EXIT_SUCCESS;
}
catch (const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
