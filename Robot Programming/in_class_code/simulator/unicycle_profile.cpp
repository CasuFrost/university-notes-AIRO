#include "laser_scanner.h"
#include "unicycle_robot.h"
#include <sys/time.h>
#include <unistd.h>

double getTimeMs() {
  struct timeval tv;
  gettimeofday(&tv, 0);
  double ret=(double)tv.tv_sec*1000+(double)tv.tv_usec*1e-3;
  return ret;
}

int main(int argc, char** argv) {
  if (argc<2)
    return -1;

  Grid g;
  g.loadFromImage(argv[1]);

  cv::Mat cv_map=g.toCvMat();
  
  GridMapping mapping(g, 10 /* pixel per meter*/);
  WorldItem simulator(mapping);
  UnicycleRobot robot(simulator, Isometry2f(0,0,0), 0.5);
  LaserScan scan(180, -M_PI/2, M_PI/2, 0.01, 100);
  //cerr << "scan : " << &scan << endl;
  LaserScanner scanner(scan, robot, Isometry2f(1,0,0));

  double time_start=getTimeMs();
  for (int i=0; i<1000; ++i){
    //cv::Mat canvas;
    //cv_map.copyTo(canvas);
    simulator.timerTick(0.1);
    //scanner._scan.draw(canvas, scanner.poseInWorld(), mapping );
    //robot.draw(canvas);
    //cv::imshow("image", canvas);
    //int key = cv::waitKey();
  }
  double time_end=getTimeMs();
  cerr << "time: " << time_end-time_start;
}
