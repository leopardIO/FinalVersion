/*************************************************************************
	> File Name: extratest.cpp
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sat 05 Sep 2015 08:30:12 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

struct A
{
    public:
        A(int a)
        {
            aa_ = a;
        }
        ~A()
        {

        }

    private:
        int aa_;
};
/*
int main()
{
    int a = 3;
    A b(a);
    A c = A(b);
    return 1;
}
*/
