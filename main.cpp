#include <fmt/format.h>
#include <opencv2/opencv.hpp>

#include "include/armor.hpp"
#include "include/img_tools.hpp"
#include "tasks/detector.hpp"
#include "tasks/plotter.hpp"

using namespace auto_aim;

int main()
{
  Detector detector;
  Plotter plotter;
  std::list<Armor> armors;
  cv::VideoCapture video("imgs/8radps.avi");
  while (true) {
    cv::Mat bgr_img;
    video.read(bgr_img);
    armors = detector.detect(bgr_img);
    nlohmann::json data;
    data["armor_x"] = armors.front().center.x;
    data["armor_y"] = armors.front().center.y;
    plotter.plot(data);
    cv::Mat draw_armor = bgr_img.clone();
    for (const auto & armor : armors) {
      tools::draw_points(draw_armor, armor.points);
      tools::draw_text(
        draw_armor,
        fmt::format("{},{}{:.2f}", COLORS[armor.color], ARMOR_NAMES[armor.name], armor.confidence),
        armor.left.top);

        
    }
    cv::imshow("draw_armor", draw_armor);
    auto key = cv::waitKey(25);
    if (key == 'q') break;
  }
  return 0;
}
