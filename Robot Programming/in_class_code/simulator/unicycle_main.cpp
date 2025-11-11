#include "laser_scanner.h"
#include "unicycle_robot.h"

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
  UnicycleRobot robot(simulator, Isometry2f(0, 0, 0), 2);
  LaserScan scan(180, -M_PI / 2, M_PI / 2, 0.01, 1000);
  // cerr << "scan : " << &scan << endl;
  LaserScanner scanner(scan, robot, Isometry2f(5, 0, 0));

  while (1)
  {
    cv::Mat canvas;
    cv_map.copyTo(canvas);
    simulator.timerTick(0.1);
    scanner._scan.draw(canvas, scanner.poseInWorld(), mapping);
    robot.draw(canvas);
    cv::imshow("image", canvas);
    int key = cv::waitKey();
    if (key == 27)
    {
      cout << "Interrupted by the user" << endl;
      exit(0);
    }
    // cout<< key<< endl;
    float rv = 0;
    float tv = 0;

    switch (key)
    {
    case 119:
      tv = 6;
      break;
    case 97:
      rv = 0.5;
      break;
    case 115:
      tv = -6;
      break;
    case 100:
      rv = -0.5;
      break;

    default:
      1;
    }
    robot.velocity_translational = tv;
    robot.velocity_rotational = rv;
  }
}
