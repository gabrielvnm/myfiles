#include<iostream>
using namespace std;


// scanf = cin >>
// printf = cout <<
// condicional = if(){} else{}
// \n = endl
// constante = CONST, USA LETRA MAIUSCULA

int main(){

    const int N1 = 10;
    int n2;

    bool certo = n1 == n2;
    bool maior = n1 < n2;
    bool menor = n1 > n2;

    
//    cout <<"eu vejo " << n1 << " cornos" <<endl;
    cout <<"quantos cornos eu vejo?" <<endl;

    cin >> n2;
    cout << "voce falou " << n2 << endl;

    if(certo){

        cout << "parabens corno" <<endl;

    }
    else if(maior){

        cout << "bota menos" <<endl;
    }
    else if(menor){

        cout << "bota mais" <<endl;
    }



} 