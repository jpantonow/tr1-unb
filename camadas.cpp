#include "camadafisica.hpp"
#include <bitset>

using namespace std;

vector <int> CamadaFisicaTransmissora::ConversorStringBits(string mensagem) {
    vector <int> mensagemBitStream;

    for (int i {}; i < mensagem.size(); ++i) {
        bitset<8> bits(mensagem[i]);
        string bitsString =  bits.to_string();

        for (int j {}; j < bitsString.size(); ++j) {
            int bit = static_cast<int>(bitsString[j]);
            mensagemBitStream.push_back(bit-48);
        }
    }
    return mensagemBitStream;
}


void CamadaAplicacao::Transmissora(){
cout << "Escolha uma mensagem a ser codificada: " << endl;
getline(cin, mensagem);
cout << "Escolha um tipo de codificacao a ser utilizada: " << endl;
cin >> codificacao;
CamadaFisicaTransmissora camadaFisicaTransmissora;
camadaFisicaTransmissora.iniciar(codificacao,mensagem);
}

void CamadaFisicaTransmissora::iniciar(int codificacao, string mensagem){
CamadaAplicacao camadaAplicacao;
switch(codificacao){
    case BINARIA:
            quadro = ConversorStringBits(mensagem);
            fluxoBrutoDeBits = TransmissoraBinaria(quadro);
            break;
        case MANCHESTER:
            quadro = ConversorStringBits(mensagem);
            fluxoBrutoDeBits = TransmissoraManchester(quadro);
            break;
        case BIPOLAR:
            fluxoBrutoDeBits = TransmissoraBipolar(quadro);
            break;
}
camadaAplicacao.Receptora(fluxoBrutoDeBits);
}

vector <int> CamadaFisicaTransmissora::TransmissoraBinaria(vector <int> quadro){
return quadro;
}

vector <int> CamadaFisicaTransmissora::TransmissoraManchester(vector <int> quadro){
vector <int> tremDeBits;
for(int i = 0; i < quadro.size(); i++){
    tremDeBits.push_back(CLOCK[0] ^ quadro[i]);
    tremDeBits.push_back(CLOCK[1] ^ quadro[i]);
}
return tremDeBits;

}

vector <int> CamadaFisicaTransmissora::TransmissoraBipolar(vector <int> quadro){
    vector <int> tremDeBits;
    int sinal {};

    for(int i = 0; i < quadro.size(); ++i) {
        if (quadro[i]) {
            if (sinal) {
                tremDeBits.push_back(-1);
            } else {
                tremDeBits.push_back(1);
            }
        } else {
            tremDeBits.push_back(0);
        }
    }
    return tremDeBits;
}


vector <int> CamadaFisicaReceptora::ReceptoraBinaria(vector <int> quadro){
    return quadro;
}

vector <int> CamadaFisicaReceptora::ReceptoraManchester(vector <int> quadro){
    return quadro;
}
vector <int> CamadaAplicacao::Receptora(vector <int> fluxoBrutoDeBits){
    Mensagem();
    for(int i=0;i<fluxoBrutoDeBits.size(); i++){
        if(i%8 == 0){
            cout <<"\n" << fluxoBrutoDeBits[i];
        }
        else{
        cout << fluxoBrutoDeBits[i];
        }
    }
}

void CamadaAplicacao::Mensagem(){
    cout << "O codigo codificado pode ser representado por: " << endl;
}
