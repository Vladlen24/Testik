#include <iostream>
#include <ctime>
using namespace std;
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
int main()
{
    srand(time(NULL));
    double  R;
    const double pi = 3.14159265358979323846;
    cin >> R;
    int n = 1000000, m = 0;
    for (int i = 0; i < n; ++i)
    {
        double x = fRand(-R, R);
        double y = fRand(-R, R);
        double z = fRand(-R, R);
        if (x * x + y * y + z * z < R * R) m++;
    }
    cout << "V = " << R << " " << (double)m/n*8*R*R*R << " " << 4.0/3*pi*R*R*R << endl;

    return 0;
}