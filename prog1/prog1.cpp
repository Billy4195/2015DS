#include <iostream>
#include "P1_0316048.h" // your header file

int  main()
{
  // first polynomial (x^2*y^3 + 2*x^2*y - 3*x*y^2 - 4*y + 5)
  SparsePoly2D P1;
  int P1_x_exp[] = {2, 2, 1, 0, 0};
  int P1_y_exp[] = {3, 1, 2, 1, 0};
  double P1_coef[] = {1, 2, -3, -4, 5};
  P1.SetTerms(P1_x_exp, P1_y_exp, P1_coef, 5);
  cout << "P1: ";  P1.Print();  cout << endl;
  // second polynomial (2*x^2*y^2 - x^2*y + 3*x*y^2 + x - 2*y + 1)
  SparsePoly2D P2;
  int P2_x_exp[] = {2, 2, 1, 1, 0, 0};
  int P2_y_exp[] = {2, 1, 2, 0, 1, 0};
  double P2_coef[] = {2, -1, 3, 1, -2, 1};
  P2.SetTerms(P2_x_exp, P2_y_exp, P2_coef, 6);
  cout << "P2: ";  P2.Print();  cout << endl;
  // addition
  SparsePoly2D P3 = P1; // this will use your assignment operator
  P3.Add(P2);
  cout << "P3 = P1 + P2: ";  P3.Print();  cout << endl;
  // evaluation
  cout << "P1(1,2) = " << P1.Eval(1,2) << endl;
  cout << "P3(-1,1) = " << P3.Eval(-1,1) << endl;
}
