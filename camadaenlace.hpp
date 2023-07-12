#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include "camadafisica.hpp"
using namespace std;

class CamadaEnlace{
    public:
    vector <int> quadroEnquadrado;
    vector <int> crc{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
                              0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    int tipoDeEnquadramento = 0;
};


class CamadaEnlaceTransmissora: public CamadaEnlace {
    public:
        vector <int> ContagemDeCaracteres(vector <int> quadro); 
        vector <int> InsercaoDeBytes(vector <int> quadro);
        vector <int> ControleDeErroCRC(vector <int> quadro);
        vector <int> ControleDeErroBitParidadePar(vector <int> quadro);
};



class CamadaEnlaceReceptora: public CamadaEnlace {
    public:
         int ContagemDeCaracteres(vector <int> quadro); 
         vector <int> InsercaoDeBytes(vector <int> quadro);
         vector <int> ControleDeErroCRC(vector <int> quadro);
         vector <int> ControleDeErroBitParidadePar(vector <int> quadro);
};

