#include <iostream>
#include <math.h>

using namespace std;

//Aluna Maria Eduarda Alves Martim
/*

Polinômio é uma expressão algébrica de soma de monômios. 
Um monômio é uma expressão algébrica que pode ser representada por um número real multiplicado por uma ou mais variáveis
elevadas a expoentes inteiros não negativos.

- A primeira opção do código é a soma, onde são lido dois polimônios e somamos aqueles que tem o expoente igual.
- A segunda opção é a subtração, que acontece o mesmo processo da soma, mas multiplicamos o segundo polinômio por -1
e somamos com a mesma função utilizada anteriormente.
- A terceira opção é o valor numérico, onde o usuário digita um valor para a variável x e o programa lê o polinômio
e substitui aqueles que tiverem x pelo valor digitado.
- A quarta opção é a multiplicação por escalar, onde o usuário digita um valor para o escalar e o programa lê o polinômio
e multiplica todos os monomios do polinomio pela constante.
- A quinta opção é a multiplicação termo a termo, onde o programa lê dois polinômios e multiplica todos os monomios do primeiro
com todos os monomios do segundo
- A sexta e última opção é a multiplicação de polinômio por monomio, onde o programa lê um polinômio e um monômio 
e multiplica todos os monômios do polinômio pelo monômio digitado pelo usuário

*/

struct Monomio{
    int coeficiente;
    int expoente;
};

struct Polinomio{
    Monomio m[30];
    int qtd;
};

void lerMonomio(Monomio &m){
    cout << "Coeficiente: ";
    do{
    cin >> m.coeficiente; //ler coeficiente
    }while(m.coeficiente==0);
    
    cout << "Expoente: ";
    cin >> m.expoente; //leitura de expoente
    
}

void imprimirMonomio(Monomio m){ //impressão de cada monomio
    if (m.coeficiente != 0){
        cout << m.coeficiente;
    }
    else if (m.coeficiente==0){
        cout<<"";
    }
    
    if (m.expoente==1){
        cout<<"x";
    }
    else if (m.expoente != 0){
        cout << "x^" << m.expoente;
    }
    else if (m.expoente==0){
        cout<<"";
    }
}

void semelhantes(Polinomio &p){
    for (int i=0; i<p.qtd; i++){
        for (int j=i+1; j<p.qtd; j++){
            if (p.m[i].expoente==p.m[j].expoente){
                p.m[i].coeficiente+=p.m[j].coeficiente;
                p.m[j].coeficiente=0; //retirar este monomio com coef 0
                p.m[j].expoente=0; //retirar este monomio com coef 0
            }
        }
    }
}

void limpeza(Polinomio &p){ //retirar monomios com coef 0
    for (int i=0; i<p.qtd; i++){
        if (p.m[i].coeficiente==0){ 
            for (int j=i; j<p.qtd; j++){
                p.m[j].coeficiente=p.m[j+1].coeficiente;
                p.m[j].expoente=p.m[j+1].expoente;
            }
            p.qtd--;
        }
    }
}

int valornumerico(Polinomio p, int x){ //substituir X pelo valor digitado pelo usuario
    int resultado=0;
    for (int i=0; i<p.qtd; i++){
        resultado+=p.m[i].coeficiente*pow(x, p.m[i].expoente);
    }
    return resultado;
}

Polinomio somar(Polinomio p1, Polinomio p2, Polinomio &p3){  //somar os coeficientes de monomios com o mesmo expoente
    p3.qtd=p1.qtd+p2.qtd;
    for (int i=0; i<p1.qtd; i++){
        p3.m[i].coeficiente=p1.m[i].coeficiente;
        p3.m[i].expoente=p1.m[i].expoente;
    }
    for (int i=p1.qtd; i<p3.qtd; i++){
        p3.m[i].coeficiente=p2.m[i-p1.qtd].coeficiente;
        p3.m[i].expoente=p2.m[i-p1.qtd].expoente;
    }
    semelhantes(p3);
    limpeza(p3);
    return p3;
}

Polinomio subtrair(Polinomio p1, Polinomio p2, Polinomio &p3){ //multiplicar o segundo polinomio por -1 e somar
    for (int i=0; i<p2.qtd; i++){
        p2.m[i].coeficiente=p2.m[i].coeficiente*(-1);
    }
    somar(p1, p2, p3);
    semelhantes(p3);
    limpeza(p3);
    return p3;
}

Polinomio mult_escalar(Polinomio p1, int escalar, Polinomio &p3){ //multiplicar todos os coeficientes por um escalar
    p3.qtd=p1.qtd;
    for (int i=0; i<p1.qtd; i++){
        p3.m[i].coeficiente=p1.m[i].coeficiente*escalar;
        p3.m[i].expoente=p1.m[i].expoente;
    }
    semelhantes(p3);
    limpeza(p3);
    return p3;
}

Polinomio mult_termo(Polinomio p1, Polinomio p2, Polinomio &p3){ //multiplicar todos os monomios do primeiro polinomio por todos os monomios do segundo polinomio
    p3.qtd=p1.qtd*p2.qtd;
    for (int k=0; k<p3.qtd;){
    for (int i=0; i<p1.qtd; i++){
        for (int j=0; j<p2.qtd; j++){
            p3.m[k].coeficiente=p1.m[i].coeficiente*p2.m[j].coeficiente;
            p3.m[k].expoente=p1.m[i].expoente+p2.m[j].expoente;
            k++;
            }
        }
    }
    semelhantes(p3);
    limpeza(p3);
    return p3;

}
Polinomio mult_monomio(Polinomio p1, Monomio m, Polinomio &p3){ //multiplicar todos os monomios do primeiro polinomio por um monomio
    p3.qtd=p1.qtd;
    for (int i=0; i<p1.qtd; i++){
        p3.m[i].coeficiente=p1.m[i].coeficiente*m.coeficiente;
        p3.m[i].expoente=p1.m[i].expoente+m.expoente;
    }
    semelhantes(p3);
    limpeza(p3);
    return p3;
}

void printPolinomio(Polinomio p){ //mostrar os polinomios
    for (int i=0; i<p.qtd; i++){
        imprimirMonomio(p.m[i]);
        if (i < p.qtd - 1 and p.m[i+1].coeficiente!=0){
            cout << " + ";
        }  
    }
}

main(){
    Polinomio p1, p2, p3;
    int opcao;

    do{
    cout<<endl;
    cout<<"1 - Somar polinomios"<<endl;
    cout<<"2 - Subtrair polinomios"<<endl;
    cout<<"3 - Calcular valor numerico de polinomio"<<endl;
    cout<<"4 - Multiplicar polinomios por escalar"<<endl;
    cout<<"5 - Multiplicar polinomios termo a termo"<<endl;
    cout<<"6 - Multiplicar polinomio por monomio"<<endl;
    cout<<"0 - Sair"<<endl;
    cin>>opcao;

    switch (opcao){

        case 1:
            system("cls");
            cout<<endl<<"Polinomio 1"<<endl; //leitura de polinomios
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p1.qtd;
            }while (p1.qtd<1 or p1.qtd>10);
            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }
            cout<<"Polinomio 2"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p2.qtd;
            }while (p2.qtd<1 or p2.qtd>10);
            for (int i=0; i<p2.qtd; i++){
                lerMonomio(p2.m[i]);
            }
            somar(p1, p2, p3); //soma de polinomios
            cout<<"(";//impressao de polinomios
            printPolinomio(p1);
            cout<<") + ("; 
            printPolinomio(p2);
            cout<<") = ";
            printPolinomio(p3);;
            break;

        case 2:
            system("cls");

            cout<<endl<<"Polinomio 1"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p1.qtd;
            }while (p1.qtd<1 or p1.qtd>10); //ate 10 monomios no polinomio

            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }


            cout<<"Polinomio 2"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p2.qtd;
            }while (p2.qtd<1 or p2.qtd>10);

            for (int i=0; i<p2.qtd; i++){
                lerMonomio(p2.m[i]);
            }


            subtrair(p1, p2, p3);
            cout<<"(";
            printPolinomio(p1);
            cout<<") - (";
            printPolinomio(p2);
            cout<<") = ";
            printPolinomio(p3);
            break;

        case 3:
            system("cls");

            cout<<endl<<"Polinomio 1"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p1.qtd;
            }while (p1.qtd<1 or p1.qtd>10);

            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }


            cout<<"Valor numerico: ";
            int x;
            cin>>x;

            cout<<"(";
            printPolinomio(p1);
            cout<<") sendo x = "<<x<<endl;
            cout<<"Resultado: "<<valornumerico(p1, x);
            break;

        case 4:
            system("cls");

            cout<<endl<<"Polinomio 1"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p1.qtd;
            }while (p1.qtd<1 or p1.qtd>10);

            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }

            cout<<"Escalar: ";
            int escalar;
            cin>>escalar;

            mult_escalar(p1, escalar, p3);
            cout<<"("; 
            printPolinomio(p1);
            cout<<") * ("<<escalar<<") = ";
            printPolinomio(p3);
            break;

        case 5:
            system("cls");

            cout<<endl<<"Polinomio 1"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p1.qtd;
            }while (p1.qtd<1 or p1.qtd>10);

            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }


            cout<<"Polinomio 2"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p2.qtd;
            }while (p2.qtd<1 or p2.qtd>10);

            for (int i=0; i<p2.qtd; i++){
                lerMonomio(p2.m[i]);
            }


            cout<<"(";
            printPolinomio(p1);
            cout<<") * (";
            printPolinomio(p2);
            cout<<") = ";
            mult_termo(p1, p2, p3);
            printPolinomio(p3);
            break;

        case 6:
            system("cls");

            cout<<endl<<"Polinomio 1"<<endl;
            do{
            cout<<"Quantidade de monomios (limite 10): ";
            cin>>p1.qtd;
            }while (p1.qtd<1 or p1.qtd>10);

            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }

            cout<<"Monomio para multiplicar"<<endl;
            lerMonomio(p2.m[0]);

            cout<<"(";
            printPolinomio(p1);
            cout<<") * (";
            imprimirMonomio(p2.m[0]);
            cout<<") = ";
            mult_monomio(p1, p2.m[0], p3);
            printPolinomio(p3);
            break;


        case 0:
            break;

        default:
            cout<<"Opcao invalida"<<endl;
            break;
    
        }

    }while (opcao!=0);

}
