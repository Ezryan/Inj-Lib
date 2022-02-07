#include <iostream>
#include <vector>
using namespace std;

//helping_functions//
double npow(double a, int b)
{
    double ans = 1;

    for(int i = 0; i < b; ++i)
        ans *= a;

    return ans;
}
/////////////////////
inline double absdif(double a, double b)
{
    return abs(a-b);
}
/////////////////////

class func
{
public:
    /* data */
    vector <double> koefs;

    func(double mas[], int SIZE);

    double X(double x)
    {
        double ans = 0;

        for(int i = 0; i < koefs.size(); ++i)
            ans += koefs[i]*npow(x,i);

        return ans;
    }
};

func::func(double mas[], int SIZE)
{
    for(int i = 0; i < SIZE; ++i)
    {
        koefs.push_back(mas[i]);
    }
}

void ShowF_x(func F)
{
    for (int i = F.koefs.size() - 1; i > 0; --i)
    {
        if (F.koefs[i] == 0.0)
            continue;
        else if (F.koefs[i] == 1.0)
            cout << "X^" << i << "+";
        else
            cout << F.koefs[i] << "X^" << i << "+";
    }
    cout << F.koefs[0] << endl;
}

func Derivative(func F)
{
    for (int i = 1; i < F.koefs.size(); ++i)
    {
        F.koefs[i-1] = i*F.koefs[i];
    }

    F.koefs.pop_back();

    func Fs = F;

    return Fs;        
}

func Integral(func F, double C)
{

    double ks[F.koefs.size()];

    for(int i = 0; i < F.koefs.size(); ++i)
        ks[i] = F.koefs[i]; 

    F.koefs.push_back(0);

    for (int i = 0; i < F.koefs.size(); ++i)
        F.koefs[i+1] = ks[i]/(i+1);

    F.koefs[0] = C;

    func I = F;

    return I;
}

double FuncEq(func F, double X0)
{
    double Xn1;

    func Fs = Derivative(F);

    do
    {
        Xn1 = X0;
        X0 = Xn1 - F.X(Xn1)/Fs.X(Xn1);
    } while (absdif(X0, Xn1) > 0.000001);

    return X0;
}
