#include "laser_scanner.h"
#include <unistd.h>

int main(int argc, char **argv)
{
  if (argc < 2)
    return -1;

  Grid g;
  g.loadFromImage(argv[1]);

  cv::Mat cv_map = g.toCvMat();

  GridMapping mapping(g, 10 /* pixel per meter*/);
  WorldItem simulator(mapping);
  LaserScan scan(180, -M_PI / 2, M_PI / 2, 0.01, 1000);
  cerr << "scan : " << &scan << endl;
  LaserScanner scanner(scan, simulator, Isometry2f(0, 0, 0));

  while (1)
  {
    cv::Mat canvas;
    cv_map.copyTo(canvas);
    simulator.timerTick(0.1);
    scanner._scan.draw(canvas, scanner.poseInWorld(), mapping);
    cv::imshow("image", canvas);
    /*cout << endl;
    for (int i = 0; i < scan.ranges_num; ++i)
    {
       cout << scan.ranges[i] << " ";
    }*/

    /*
cv::line(canvas,
         cv::Point(origin.y(), origin.x()),
         cv::Point(hit.y(), hit.x()),
         cv::Scalar(127), 1);
cerr << "hit: " << hit
     << " hit_w" << mapping.grid2world(Vector2i(hit.x(), hit.y()))
     << " hit_p" << mapping.world2grid(mapping.grid2world(Vector2i(hit.x(), hit.y()))) << endl;
*/

    int key = cv::waitKey();
    cout << key << endl;
    float da = 0;
    float dx = 0;
    switch (key)
    {
    case 119:
      dx = 0.1;
      break;
    case 97:
      da = 0.05;
      break;
    case 115:
      dx = -0.1;
      break;
    case 100:
      da = -0.05;
      break;
    default:
      1;
    }
    Isometry2f d_iso(dx, 0, da);
    scanner._pose_in_parent = scanner._pose_in_parent * d_iso;
  }
}
