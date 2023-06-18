#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
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
    vector <int> CLOCK = {0, 1};
    public:
    void iniciar(int codificacao, string mensagem);
    vector <int> TransmissoraBinaria(vector <int> quadro);
    vector <int> TransmissoraManchester(vector <int> quadro);
    vector <int> TransmissoraBipolar(vector <int> quadro);
    vector <int> ConversorStringBits(string mensagem);
};
class CamadaFisicaReceptora: public Camada {
    public:
    vector <int> ConversorBinarioBits(vector <int> quadro);
    vector <int> ConversorManchesterBits(vector <int> quadro);
    vector <int> ConversorBipolarBits(vector <int> quadro);
    string ConversorBitString(vector<int> bitstream);
    string ReceptoraBinaria(vector <int> quadro);
    string ReceptoraManchester(vector <int> quadro);
    string ReceptoraBipolar(vector <int> quadro);
};
class CamadaAplicacao: public Camada {
    private:
    const static int BINARIA = 0;
    const static int MANCHESTER = 1;
    const static int BIPOLAR = 2;
    public:
    string mensagem;
    void Transmissora();
    vector <int> Receptora(vector <int> fluxoBrutoDeBits, int codificacao);
    void MensagemCodificada(vector <int> fluxoBrutoDeBits, int codificacao);
    void MensagemRecebida(string);
};

class MeioDeComunicacao{
    private:
    public:
    vector <int> Comunicacao(vector <int> fluxoBrutoDeBits);
};

