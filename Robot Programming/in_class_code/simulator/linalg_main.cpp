#include "linalg.h"
#include <iostream>
using namespace std;

/*
cerr << stuff_1 << stuff_2 << .... << endl;

 
a + (stuff_1 + (stuff_2 ..._) )

struct MyStruct {
  int val1;
  int val2;
};

ostream& operator<<(ostream & os, const MyStruct& b) {
  os << b.val1 << " " << b.val2;
  return os;
}

MyStruct s1, s2;

cout << s1 << s2  << "cose" << endl;

*/

int main (int argc, char** argv) {
  Vector2f zerov(0,0);
  cout << zerov << endl;

  Rotation2f roto(0.1);
  cout << roto << endl;

  cout << roto * roto.transpose() << endl;

  Vector2f unox(1,0);
  Vector2f unoy(0,1);
  cout << roto * unox << endl;
  cout << roto * unoy << endl;

  Isometry2f iso(1, 2, 0.1);

  cout << unox + unoy << endl;
  cout << iso << endl;
  cout << iso * unox << endl;
  cout << iso * unoy << endl;

  auto unoxdopotf = iso * unox;
  auto unoydopotf = iso * unoy;

  cout << iso.inverse()*iso << endl;
  cout << iso*iso.inverse() << endl;

  cout << iso.inverse()*unoxdopotf;
  cout << iso.inverse()*unoydopotf;
  
  
}
