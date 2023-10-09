#include <iostream>
#include <math.h>

using namespace std;

struct Monomio{
    int coeficiente;
    int expoente;
};

struct Polinomio{
    Monomio m[10];
    int qtd;
};

void lerMonomio(Monomio &m){
    cout << "Coeficiente: ";
    cin >> m.coeficiente; //ler coeficiente
    if (m.coeficiente==0){
        m.expoente=0;
        cout<<"Expoente: "<<m.expoente<<endl;
    }
    else{
    cout << "Expoente: ";
    cin >> m.expoente; //leitura de expoente
    }
}

void imprimirMonomio(Monomio m){
    if (m.coeficiente==1){
        cout<<"";
    }
    else if (m.coeficiente==-1){
        cout<<"-";
    }
    else if (m.coeficiente != 0){
        cout << m.coeficiente;
    }
    
    if (m.expoente==1){
        cout<<"x ";
    }
    else if (m.expoente != 0){
        cout << "x^" << m.expoente;
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

Polinomio subtrair(Polinomio p1, Polinomio p2, Polinomio &p3){
    for (int i=0; i<p2.qtd; i++){
        p2.m[i].coeficiente=p2.m[i].coeficiente*(-1);
    }
    somar(p1, p2, p3);
    semelhantes(p3);
    limpeza(p3);
    return p3;
}

Polinomio mult_escalar(Polinomio p1, int escalar, Polinomio &p3){
    p3.qtd=p1.qtd;
    for (int i=0; i<p1.qtd; i++){
        p3.m[i].coeficiente=p1.m[i].coeficiente*escalar;
        p3.m[i].expoente=p1.m[i].expoente;
    }
    semelhantes(p3);
    limpeza(p3);
    return p3;
}

Polinomio mult_termo(Polinomio p1, Polinomio p2, Polinomio &p3){ 
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

void printPolinomio(Polinomio p){
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
    cout<<endl<<"1 - Somar polinomios"<<endl;
    cout<<"2 - Subtrair polinomios"<<endl;
    cout<<"3 - Calcular valor numerico de polinomio"<<endl;
    cout<<"4 - Multiplicar polinomios por escalar"<<endl;
    cout<<"5 - Multiplicar polinomios termo a termo"<<endl;
    cout<<"0 - Sair"<<endl;
    cin>>opcao;

    switch (opcao){

        case 1:
            system("cls");
            cout<<endl<<"Polinomio 1"<<endl; //leitura de polinomios
            do{
            cout<<"Quantidade de monomios: ";
            cin>>p1.qtd;
            }while (p1.qtd<1);
            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }
            cout<<"Polinomio 2"<<endl;
            do{
            cout<<"Quantidade de monomios: ";
            cin>>p2.qtd;
            }while (p2.qtd<1);
            for (int i=0; i<p2.qtd; i++){
                lerMonomio(p2.m[i]);
            }
            somar(p1, p2, p3); //soma de polinomios
            cout<<"(";//impressao de polinomios
            printPolinomio(p1);
            cout<<") + ("; 
            printPolinomio(p2);
            cout<<") = ";
            printPolinomio(p3);
            break;

        case 2:
            system("cls");

            cout<<endl<<"Polinomio 1"<<endl;
            do{
            cout<<"Quantidade de monomios: ";
            cin>>p1.qtd;
            }while (p1.qtd<1);

            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }


            cout<<"Polinomio 2"<<endl;
            do{
            cout<<"Quantidade de monomios: ";
            cin>>p2.qtd;
            }while (p2.qtd<1);

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
            cout<<"Quantidade de monomios: ";
            cin>>p1.qtd;
            }while (p1.qtd<1);

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
            cout<<"Quantidade de monomios: ";
            cin>>p1.qtd;
            }while (p1.qtd<1);

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
            cout<<"Quantidade de monomios: ";
            cin>>p1.qtd;
            }while (p1.qtd<1);

            for (int i=0; i<p1.qtd; i++){
                lerMonomio(p1.m[i]);
            }


            cout<<"Polinomio 2"<<endl;
            do{
            cout<<"Quantidade de monomios: ";
            cin>>p2.qtd;
            }while (p2.qtd<1);

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

        case 0:
            break;

        default:
            cout<<"Opcao invalida"<<endl;
            break;

    }


    }while (opcao!=0);
}
