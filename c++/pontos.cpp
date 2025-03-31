#include <iostream> // lib padrao
#include <cstdlib> // lib de umas funções ai
#include <ctime> //lib de tempo
using namespace std;


// scanf = cin >>
// printf = cout <<
// condicional = if(){} else{}
// \n = endl
// constante = CONST, USA LETRA MAIUSCULA
// for = do mesmo jeito
// while tambem é igual

int main(){

    //seed do numero
    srand(time(NULL));
    //criar um numero aleatorio com resto da divisao
    const int N1 = rand()%100;
    bool errado = true;
    int tentativas = 0;

    double pontos = 1000.0;
    int n3;

    cout << "digita ai um numero" <<endl;
    cin >> n3;


    for(tentativas = 1; tentativas<=n3; tentativas++){

        int n2;

        cout <<"quantos cornos eu vejo?" <<endl;
        cin >> n2;

        double redux = abs(n2-N1)/2.0;
        pontos = pontos - redux;

        cout << "voce falou " << n2 << endl;

        bool certo = N1 == n2;
        bool maior = N1 > n2;

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
    if(errado == true){
        cout << "perdeu otario" <<endl;
    }    
    else{

        cout <<"foram " << tentativas << " tentativas" <<endl;
        //meu deus isso tudo aqui em baixo só pra botar duas casas depois da virgula
        cout.precision(2); //isso coloca em notação cientifica kkkk
        cout << fixed;// isso faz a posição da virgula fixar fixa

        cout << pontos << " pontos" <<endl;
    }
} 