#include "LIB_Util.h"
#include <iostream>

using namespace std;

int main()
{
struct point* p = new point [5];
for(int i = 0;i<5;i++)
{
	p[i].a = new double [2];
	for(int j = 0;j<2;j++)
		p[i].a[j] = 3;
}
p = scale(2,p,5);

for(int i = 0;i<5;i++)
{
	cout<<"["<<endl;
	for(int j = 0;j<2;j++)
		cout<<p[i].a[j];
	cout<<"]"<<endl;
}

return 0;
}
