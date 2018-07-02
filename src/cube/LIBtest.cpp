#include <iostream>

#include "LIB_Util.h"
#include "point.h"

using namespace std;

int main()
{
  struct point* p = new struct point[5];
  double a [5][5] = {{1,2,3,4,5},
                    {5,4,3,2,1},
                    {6,7,8,9,0},
                    {0,7,8,9,6},
                    {3,4,5,6,7}};

  for(int i = 0;i<5;i++)
  {
  	p[i].a = a[i];
  }
  
  p = scale(5,p,5);

  for(int i = 0;i<5;i++)
  {
  	cout<<"[";
  	for(int j = 0;j<5;j++)
  		cout<<p[i].a[j]<< " ";
  	cout<<"]"<<endl;
  }

  p = transformforth(2, 5, p, 5);
  for(int i = 0;i<5;i++)
  {
  	cout<<"[";
  	for(int j = 0;j<5;j++)
  		cout<<p[i].a[j]<< " ";
  	cout<<"]"<<endl;
  }

  p = transformback(2, 5, p, 5);
  for(int i = 0;i<5;i++)
  {
    cout<<"[";
    for(int j = 0;j<5;j++)
      cout<<p[i].a[j]<< " ";
    cout<<"]"<<endl;
  }


return 0;
}
