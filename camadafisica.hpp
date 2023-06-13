#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
class Camada {
    public:
    vector <int> quadro;
    vector <int> fluxoBrutoDeBits;
};

class CamadaFisica: public Camada {
    private:
    public:
    int codificacao;
    const static int BINARIA = 0;
    const static int MANCHESTER = 1;
    const static int BIPOLAR = 2;
    int TransmissoraBinaria();
    int TransmissoraManchester();
    int TransmissoraBipolar();
    int ReceptoraBinaria(vector <int> quadro);
    int ReceptoraManchester(vector <int> quadro);
    int ReceptoraBipolar(vector <int> quadro);

};

class CamadaAplicacao: public Camada {
    private:
    public:
    string mensagem;
    void Transmissora(vector <int> quadro);
    void Receptora(vector <int> quadro);
    void Mensagem(string);
};



