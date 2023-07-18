#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;

class CamadaEnlace{
    private:
    public:
    const static int CONTAGEM = 0;
    const static int INSERCAO = 1;
    const static int PARIDADE = 0;
    const static int CRC = 1;
    const static int HAMMING = 2;
    vector <int> quadroEnquadrado;
    vector <int> crc{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
                              0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    vector <int> flag{0,0,0,0,1,1,1,1};
    vector <int> esc{0,0,0,0,0,1,1,0};
    int tipoDeEnquadramento = 0;
    vector <int> int_byte(int size);
    vector <int> inserir_bytes(vector <int> byte, vector<int> quadro);
    vector <int> complementode1(vector <int> numero);
    vector <int> somabinaria(vector <int>, vector<int>);
    vector <vector <int>> dividirquadro(vector <int>);
    vector <vector <int>> dividirhamming(vector <int>);
    vector <int> calculoparidade(vector <int>);
};


class CamadaEnlaceTransmissora: public CamadaEnlace {
    public:
        vector <int> ContagemDeCaracteres(vector <int> quadro); 
        vector <int> InsercaoDeBytes(vector <int> quadro);
        vector <int> ControleDeErroCRC(vector <int> quadro);
        vector <int> ControleDeErroBitParidadePar(vector <int> quadro);
        vector <int> codificacaoHamming(vector <int>);
        vector <int> iniciar(int erro, int enquadramento, vector <int>);
};



class CamadaEnlaceReceptora: public CamadaEnlace {
    public:
         vector <int> ContagemDeCaracteres(vector <int> quadro); 
         vector <int> InsercaoDeBytes(vector <int> quadro);
         vector <int> ControleDeErroCRC(vector <int> quadro);
         vector <int> ControleDeErroBitParidadePar(vector <int> quadro);
         vector <int> decodificacaoHamming(vector <int>);
         vector <int> iniciar(int erro, int enquadramento, vector <int>);
};

