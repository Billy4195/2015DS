#include "P4_0316048.h"
int main()
{
  PolyBST p1, p2, p3;
  p1.setTerm(2,2);
  p1.setTerm(0,-1);
  cout << "p1 = " << p1 << endl;  // 2*x^2 ¡V 1
  p2.setTerm(0,1);   p2.setTerm(2,2);
  cout << "p2 = " << p2 << endl;  // 2*x^2 + 1
  p3 = p1 * p2;
  cout << "p1*p2 = " << p3 << endl; // 4*x^4 ¡V 1
  p3 = p1 + p2;
  cout << "p1+p2 = " << p3 << endl; // 4*x^2
  p3 = p1 - p2;
  cout << "p1¡Vp2 = " << p3 << endl; // ¡V2
  p1.setTerm(2,3);   p1.setTerm(1,2);  p1.setTerm(0,0);
  cout << "p1 = " << p1 << endl;  // 3*x^2 + 2*x^1
  p3 = p1 * 2;
  cout << "p1*2 = " << p3 << endl; // 6*x^2 + 4*x^1
  p3 = p1 * 2 - p2;
  cout << "p1*2-p2 = " << p3 << endl; // 4*x^2 + 4*x^1 - 1
  system("pause");
  return 0;
}
