#include "grid.h"
#include "grid_mapping.h"

int main(int argc, char** argv) {
  if (argc<2)
    return -1;

  Grid g;
  g.loadFromImage(argv[1]);

  cv::Mat canvas=g.toCvMat();
  
  Vector2f origin(g._rows/2, g._cols/2);
  float alpha=0;
  float alpha_inc=M_PI/180;

  GridMapping mapping(g, 10 /* pixel per meter*/);
  
  while (1) {
    Vector2f hit;
    cerr << "alpha: " << alpha << endl;
    if (! g.scanRay(hit, origin, alpha, 20, 1000)) {
      cerr << "miss" << endl;
    }
    cv::imshow("image", canvas);

    Vector2f world_origin(0,0);
    
    cv::line(canvas,
             cv::Point(origin.y(), origin.x()),
             cv::Point(hit.y(), hit.x()),
             cv::Scalar(127), 1);
    cerr << "origin: "  
         << " origin_w " << world_origin
         << " origin_p " << mapping.world2grid(world_origin) << endl;
    cerr << "hit: " << hit
         << " hit_w " << mapping.grid2world(Vector2i(hit.x(), hit.y()))
         << " hit_p " << mapping.world2grid(mapping.grid2world(Vector2i(hit.x(), hit.y()))) << endl;
    
    cv::waitKey();
    alpha+=alpha_inc;
  }
    
}
