#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
class Camada{
    public:
    vector <int> quadro;
    int fluxoBrutoDeBits [];
};
class CamadaFisica: public Camada{
    private:
    public:
    int codificacao;
    const static int BINARIA = 0;
    const static int MANCHESTER = 1;
    const static int BIPOLAR = 2;
    int TransmissoraBinaria();
    int TransmissoraManchester();
    int TransmissoraBipolar();
    int ReceptoraBinaria(quadro);
    int ReceptoraManchester(quadro);
    int ReceptoraBipolar(quadro);

};

class CamadaAplicacao: public Camada{
    private:
    public:

    void Transmissora(quadro);
    void Receptora(quadro);
};



