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

}
vector <int> CamadaFisicaTransmissora::TransmissoraBipolar(vector <int> quadro){

}

vector <int> CamadaFisicaReceptora::ReceptoraBinaria(vector <int> quadro){
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
