#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
class Camada {
    public:
    vector <int> quadro;
    vector <int> fluxoBrutoDeBits;
    int codificacao;
};

class CamadaFisicaTransmissora: public Camada {
    public:
    void iniciar(int codificacao);
    vector <int> TransmissoraBinaria(vector <int> quadro);
    vector <int> TransmissoraManchester(vector <int> quadro);
    vector <int> TransmissoraBipolar(vector <int> quadro);
};
class CamadaFisicaReceptora: public Camada {
    public:
    vector <int> ReceptoraBinaria(vector <int> quadro);
    vector <int> ReceptoraManchester(vector <int> quadro);
    vector <int> ReceptoraBipolar(vector <int> quadro);
};
class CamadaAplicacao: public Camada {
    private:
    public:
    string mensagem;
    void Transmissora(vector <int> quadro);
    void Receptora(vector <int> quadro);
    void Mensagem(string);
    vector <int> CodificarBinario(string, vector <int> &quadro);
};



