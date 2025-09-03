#include<iostream>
#include<stdexcept>

using namespace std;

int main(){
    double num1 , num2;
    char op;
cout<<"Enter the numbers\n";
cin>>num1>>op>>num2;
    double result;
    switch (op)
    {
    case '+':
       result= num1+num2;
        break;
    
        case '-':
      result=  num1-num2;
        break;

        case '*':
       result= num1*num2;
        break;

        case '/':
        if(num2==0){
        cerr<<"Error:\n";
        return 1;
        }
       result= num1/num2;
        break;

    default:
    cerr<<"Invalid operation\n";
        return 1;
    }
    cout<<result;
    return 0;
}