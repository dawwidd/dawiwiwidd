#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    ifstream plik("profile_prędkości_V2.txt");
    double t, wl, wp, R, d;
    double f, f_p=0, x, x_p=0, y, y_p=0;

    int i=0, time;

    R = 0.1;
    d = 0.5;
    time = 10000;
    
    while(plik && i<time)
    {
        plik>>t>>wl>>wp;
        
        f = f_p + 0.01 * (1-0)*R/d;
        x = x_p + 0.01 * (1+0)*R*cos(f)/2;
        y = y_p + 0.01 * (1+0)*R*sin(f)/2;

        f_p = f;
        x_p = x;
        y_p = y;
        i++;
    }
    cout<<f<<" "<<x<<" "<<y<<endl;

    plik.close();
    return 0;
}