#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <sstream>

using namespace std;

// Binary operation
class add
{
public:
    static double execute(double a, double b)
    {
        return a + b;
    }
};

class sub
{
public:
    static double execute(double a, double b)
    {
        return a - b;
    }
};

class multiply
{
public:
    static double execute(double a, double b)
    {
        return a * b;
    }
};

class division
{
public:
    static double execute(double a, double b)
    {
        if (b == 0)
        {
            throw invalid_argument("Error");
        }
        return a / b;
    }
};

class power
{
public:
    static double execute(double a, double b)
    {
        return pow(a, b);
    }
};

class modulu
{
public:
    static double execute(double a, double b)
    {
        return fmod(a, b);
    }
};

// Basic uranary operation
class sine
{
public:
    static double execute(double a)
    {
        const double PI = 3.14159265358979323846;
        double radians = a * PI / 180.0;
        return sin(radians);
    }
};

class cosine
{
public:
    static double execute(double a)
    {
        const double PI = 3.14159265358979323846;
        double radians = a * PI / 180.0;
        return cos(radians);
    }
};

class tangent
{
public:
    static double execute(double a)
    {
        const double PI = 3.14159265358979323846;
        double radians = a * PI / 180.0;
        return tan(radians);
    }
};

class squareroot
{
public:
    static double execute(double a)
    {
        return sqrt(a);
    }
};

class square
{
public:
    static double execute(double a)
    {
        return (a * a);
    }
};

class factorial
{
public:
    static double execute(double a)
    {
        if (a < 0 || floor(a) != a)
            throw invalid_argument("factorial must be a non negative integer");

        int n = (int)a;
        double fact = 1;
        for (int i = 1; i <= n; i++)
        {
            fact *= i;
        }
        return fact;
    }
};

class logarithm
{
public:
    static double execute(double a)
    {
        return log10(a);
    }
};

class naturallogarithm
{
public:
    static double execute(double a)
    {
        return log(a);
    }
};

// making a class to use all operation class
class calculator
{
private:
    map<string, function<double(double, double)>> binaryoperation;
    map<string, function<double(double)>> uranaryoperation;
    double memory = 0.0;
    vector<string> history;

public:
    double lastresult;
    calculator()
    {
        // initialize binary operation
        binaryoperation["+"] = add::execute;
        binaryoperation["-"] = sub::execute;
        binaryoperation["*"] = multiply::execute;
        binaryoperation["/"] = division::execute;
        binaryoperation["^"] = power::execute;
        binaryoperation["mod"] = modulu::execute;

        // initialize uranary operation
        uranaryoperation["sin"] = sine::execute;
        uranaryoperation["cos"] = cosine::execute;
        uranaryoperation["tan"] = tangent::execute;
        uranaryoperation["^2"] = square::execute;
        uranaryoperation["√"] = squareroot::execute;
        uranaryoperation["!"] = factorial::execute;
        uranaryoperation["log10"] = logarithm::execute;
        uranaryoperation["ln"] = naturallogarithm::execute;
    }
    double calculate(double num1, string op, double num2 = 0)
    {
        double result;
        try
        {
            if (uranaryoperation.find(op) != uranaryoperation.end())
            {
                result = uranaryoperation[op](num1);
            }
            else if (binaryoperation.find(op) != binaryoperation.end())
            {
                result = binaryoperation[op](num1, num2);
            }
            else
            {
                throw invalid_argument("Inavalid operation");
            }
            lastresult = result;
            stringstream ss;
            if (uranaryoperation.find(op) != uranaryoperation.end())
            {
                ss << op << "(" << num1 << ") = " << result;
            }
            else
            {
                ss << num1 << " " << op << " " << num2 << " = " << result;
            }
            history.push_back(ss.str());

            return result;
        }
        catch (const exception &e)
        {
            throw;
        }
    }

    // Memory functions
    void memorystore(double value) // to store value in memory
    {
        memory = value;
    }
    void memoryrecall() {}       // to recall the memory or value
    void memoryadd(double value) // to add value to memory like memory = 10 ; value 2+5=7 then MA = 10 + 7 = 17
    {
        memory += value;
    }
    void sub(double value) // same as MA but this just subtract
    {
        memory -= value;
    }
    void memoryclear() // clear all the memory
    {
        memory = 0.0;
    }

    // History functions
    vector<string> gethistory()
    {
        return history;
    }
    void clearhistory()
    {
        history.clear();
    }
    vector<string> getbinaryops()
    {
        vector<string> ops;
        for (auto &pair : binaryoperation)
        {
            ops.push_back(pair.first);
        }
        return ops;
    }
    vector<string> geturanaryops()
    {
        vector<string> ops;
        for (auto &pair : uranaryoperation)
        {
            ops.push_back(pair.first);
        }
        return ops;
    }
};

int main()
{
    calculator cal;
    double a, b;
    string op;
    cout << "Enter the  number and operation to be performed\n";
    cin >> a >> op;
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "^" || op == "mod")
    {
        cin >> b;
        try
        {
            double result = cal.calculate(a, op, b);
            cout << "result = " << result << endl;
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << '\n';
        }
    }
    else
    {
        try
        {
            double result = cal.calculate(a, op);
            cout << "result = " << result << endl;
        }
        catch (invalid_argument &e)
        {
            cout << e.what() << '\n';
        }
    }
    return 0;
}