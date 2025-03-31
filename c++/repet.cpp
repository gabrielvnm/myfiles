#include<iostream>
using namespace std;


// scanf = cin >>
// printf = cout <<
// condicional = if(){} else{}
// \n = endl
// constante = CONST, USA LETRA MAIUSCULA
// for = 

int main(){

    const int N1 = 10;
    bool errado = true;
    int tentativas = 0;

    while(errado = true){

        tentativas++;
        int n2;

        cout <<"quantos cornos eu vejo?" <<endl;
        cin >> n2;
        cout << "voce falou " << n2 << endl;

        bool certo = N1 == n2;
        bool maior = N1 > n2;

    
//      cout <<"eu vejo " << N1 << " cornos" <<endl;
        

        

        if(certo){

            cout << "parabens corno" <<endl;
            errado = false;
            break;
        }
        else if(maior){

            cout << "bota mais" <<endl;
        }
        else {

            cout << "bota menos" <<endl;
        }
    }
    cout <<"acabouuuu" <<endl;    
    cout <<"foram " << tentativas << " tentativas" <<endl;    
} 