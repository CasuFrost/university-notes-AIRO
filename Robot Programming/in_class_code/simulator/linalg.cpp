#include "linalg.h"

std::ostream& operator << (std::ostream& os, const Vector2f& v) {
  os << "Vector2f: " << v.x() << " " << v.y();
  return os;
}

std::ostream& operator << (std::ostream& os, const Vector2i& v) {
  os << "Vector2i: " << v.x() << " " << v.y();
  return os;
}

std::ostream& operator << (std::ostream& os, const Rotation2f& r) {
  os << "Rotation2f: [ [" <<
    r._values[0][0] << " " <<  r._values[0][1] << "] [" <<
    r._values[1][0] << " " <<  r._values[1][1] << "] ]";
   return os;
}

std::ostream& operator << (std::ostream& os, const Isometry2f& iso) {
  os << "Isometry2f: " << iso._rotation << " " << iso._translation;
  return os;
}
