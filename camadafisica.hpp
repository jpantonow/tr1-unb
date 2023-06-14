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
    private:
    const static int BINARIA = 0;
    const static int MANCHESTER = 1;
    const static int BIPOLAR = 2;
    public:
    void iniciar(int codificacao, string mensagem);
    vector <int> CodificarBinario(string mensagem);
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
    void Transmissora();
    vector <int> Receptora(vector <int> fluxoBrutoDeBits);
    void Mensagem();
};



