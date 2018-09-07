#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <bitset>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

int main() {
    ifstream arq;
    arq.open("binarycode1");

    if (arq.is_open()) {
        string line = "";
        float ciclos = 0.0, ins = 0.0;
        int lw = 0, sw = 0, rtype = 0, branch = 0, jump = 0, ime = 0;

        char c[33];

        while (arq.getline(c, 33)) {
            string aux = "";
            for (int i = 0; i < 6; i++) {
                aux += c[i];
            }

            int v = atoi(aux.c_str());

            if (v < 1000 && v > 0){ // Instruções tipo j e branch
                if (v == 10 || v == 11) {
                    jump++;
                } else if (v >= 100 && v <= 110) {
                    branch++;
                }
                ciclos += 3;
                ins++;
            } else if (v >= 100011 && v <= 100101){// Load Adress 5 ciclos estao inclusas as outras instrucoes de LW
                ciclos += 5;
                ins++;
                lw++;
            } else {
                if (v == 0) {// R type instructions
                    for (int i = 26; i < 31; i++)
                        aux += c[i];

                    v = atoi(aux.c_str());

                    if (v == 1000) {// JR instruction
                        ciclos += 3;
                        ins++;
                        rtype++;
                    } else {// everyother R type instruction
                        ciclos += 4;
                        ins++;
                        rtype++;
                    }
                } else {
                    if (v >= 1000 && v <= 1111) {// I type instruction
                        ciclos += 4; // Todos as outras
                        ins++;
                        ime++;
                    } else if (v >= 101000 && v <= 101011) {// Store Word intstruction
                        ciclos += 4;
                        ins++;
                        sw++;
                    }
                }
            }
        }

        float cpi = (ciclos * 1.0) / (ins * 1.0);
        cout << "CPI = " << cpi << "\nInstrucoes = " << ins << "\nCiclos = " << ciclos << endl;
        cout << "\n\nFinal countdown" << endl;
        cout << "Load Word: " << lw << endl;
        cout << "Save Word: " << sw << endl;
        cout << "R Type Instruction: " << rtype << endl;
        cout << "Branch Instruction: " << branch << endl;
        cout << "Jump Instruction: " << jump << endl;
        cout << "I Type Instruction: " << ime << endl;
        cout << "Grand total: " << ins << endl;
        arq.close();

    }
    return 0;
}