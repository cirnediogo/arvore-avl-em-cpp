/* 
 * File:   main.cpp
 * Author: ubuntu
 *
 * Created on 3 de Dezembro de 2009, 17:02
 */

#include <stdlib.h>
#include "ArvoreAVL.h"

/*
 * 
 */
int main(int argc, char** argv) {


    ArvoreAVL Arvore(50, 50, NULL, NULL);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(27, 27);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(17, 17);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(72, 72);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(64, 64);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(53, 53);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(57, 57);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(21, 21);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(49, 49);
    Arvore.imprime();
    cout << endl;
    Arvore.insert(35, 35);
    Arvore.imprime();
    cout << endl;
    Arvore.remove(17);
    Arvore.imprime();
    cout << endl;
    Arvore.remove(64);
    Arvore.imprime();
    cout << endl;
    Arvore.remove(53);
    Arvore.remove(72);
    Arvore.imprime();
    cout << endl;

    return (EXIT_SUCCESS);
}

