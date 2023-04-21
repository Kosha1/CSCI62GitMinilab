#include "dbiguint.h"
#include <iostream>
using namespace std;

int main(){
  dbiguint a;
  dbiguint b = dbiguint("2141");
  dbiguint u = dbiguint("191912");
  u = b;
  cout<<u<<endl;

  cout<<b.size()<<endl;
  cout<<b[4]<<" "<<b[2]<<endl;
  cout<<b<<endl;
  b.reserve(10);
  cout<<b<<endl;

  dbiguint d = dbiguint("12");
  dbiguint c = dbiguint("999999");
  d+=c;
  cout<<d<<endl;

  dbiguint e = dbiguint("9");
  dbiguint f = dbiguint("5");
  e+=f;
  cout<<e<<endl;
  cout<<b+c<<endl;
  cout<<e.compare(f)<<endl;
  cout<<(e<b)<<endl;
  cout<<(e<=e)<<endl;
  cout<<(e==b)<<endl;
  cout<<(e!=e)<<endl;
  cout<<(e>=b)<<endl;
  cout<<(b>e)<<endl;

  dbiguint z = dbiguint("000005");
  z.reserve(0);
  cout<<z<<endl;
  z-= c;
  cout<<z<<endl;

  dbiguint y = dbiguint("1009001");
  dbiguint x = dbiguint("9");
  y-=x;
  cout<<y<<endl;

  dbiguint w = dbiguint("1234589");
  dbiguint v = dbiguint("535");
  w *= v;
  cout<<w<<endl;
  cout<<"LAB 10"<<endl;
  dbiguint am = dbiguint("00023536");
  cout<<am<<endl;
  am.clean();
  cout<<am<<endl;

//change 1 from Version 1

//testing merge error

  return 0;
}
