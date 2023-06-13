#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
class Camada{
    public:
    int quadro[];
};
class CamadaFisica: public Camada{
    private:

    public:
    int codificacao;
    


};

class CamadaAplicacao: public Camada{
    private:
    public:

    void Transmissora(quadro);
    void Receptora(quadro);
};



