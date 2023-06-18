#include "camadafisica.hpp"
#include <bitset>
#include <math.h>
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

string CamadaFisicaReceptora::ConversorBitString(vector <int> bitstream){
    string mensagem;
    vector <int> resultado;
for(int i = 0;i<bitstream.size();i++){
    if(i%8 == 0){
        int soma = 0;
        for(int j = 0; j < resultado.size(); j++) {
            int a = int(pow(2,j));
            soma += int(resultado[7-j]*a);
        }
        char caractere;
        caractere = char(soma);
        mensagem += caractere;
        resultado.clear();
        resultado.push_back(bitstream[i]);
        soma = 0;
    }
    else if(i==bitstream.size()-1){
        resultado.push_back(bitstream[i]);
        int soma = 0;
        for(int j = 0; j < resultado.size(); j++) {
            int a = int(pow(2,j));
            soma += int(resultado[7-j]*a);
        }
        char caractere;
        caractere = char(soma);
        mensagem += caractere;
        resultado.clear();
        resultado.push_back(bitstream[i]);
        soma = 0;
    }
    else{
     resultado.push_back(bitstream[i]);
    }
 }
 return mensagem;
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
    MeioDeComunicacao meioDeComunicacao;
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
            quadro = ConversorStringBits(mensagem);
            fluxoBrutoDeBits = TransmissoraBipolar(quadro);
            break;
}
vector <int> fluxoComunicado = meioDeComunicacao.Comunicacao(fluxoBrutoDeBits);
camadaAplicacao.Receptora(fluxoComunicado, codificacao);
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
                tremDeBits.push_back(11);
                sinal = 0;
            } else {
                tremDeBits.push_back(10);
                sinal = 1;
            }
        } else {
            tremDeBits.push_back(0);
    }
}
return tremDeBits;
}

vector <int> CamadaFisicaReceptora::ConversorManchesterBits (vector <int> quadro) {
    vector <int> bitstream;

    for (int i = 0; i < quadro.size()/2; ++i) {
        if (quadro[i*2]) {
            bitstream.push_back(1);
        } else {
            bitstream.push_back(0);
        }
    }
    return bitstream;
}

 vector <int> CamadaFisicaReceptora::ConversorBinarioBits (vector <int> quadro) {
     vector <int> bitstream;
     for (int i = 0; i < quadro.size(); ++i) {
         if (quadro[i]) {
             bitstream.push_back(1);
         } else {
             bitstream.push_back(0);
         }
     }
 
     return bitstream;
 }

vector <int> CamadaFisicaReceptora::ConversorBipolarBits (vector <int> quadro) {
    vector <int> bitstream;

    for (int i = 0; i < quadro.size(); ++i) {
        if (quadro[i]) {
            bitstream.push_back(1);
        } else {
            bitstream.push_back(0);
        }
    }
 
    return bitstream;
}

string CamadaFisicaReceptora::ReceptoraBinaria(vector <int> quadro){
    string mensagem = ConversorBitString(quadro);
    return mensagem;
}

string CamadaFisicaReceptora::ReceptoraManchester(vector <int> quadro){
    vector <int> bitstream = ConversorManchesterBits(quadro);
    string mensagem = ConversorBitString(bitstream);
    return mensagem;
}

string CamadaFisicaReceptora::ReceptoraBipolar(vector <int> tremDeBits){
    vector <int> bitstream = ConversorBipolarBits(tremDeBits);
    string mensagem = ConversorBitString(bitstream);
    return mensagem;
}
vector <int> CamadaAplicacao::Receptora(vector <int> fluxoBrutoDeBits, int codificacao){
    MensagemCodificada();
    CamadaFisicaReceptora receptora;
    string mensagem;
    for(int i=0;i<fluxoBrutoDeBits.size(); i++){
        if(codificacao==2){
            if(i%8 == 0){
            cout <<"\n0" << fluxoBrutoDeBits[i];
        }
        else{
        if(fluxoBrutoDeBits[i] == 11 or fluxoBrutoDeBits[i] == 10){
            cout << " " << fluxoBrutoDeBits[i];
        }
        else{
            cout << " 0" << fluxoBrutoDeBits[i];
        }
        }
        }
        else{
        if(i%8 == 0){
            cout <<"\n" << fluxoBrutoDeBits[i];
        }
        else{
        if(fluxoBrutoDeBits[i] == 11 or fluxoBrutoDeBits[i] == 10){
            cout << " " << fluxoBrutoDeBits[i];
        }
        else{
            cout << "  " << fluxoBrutoDeBits[i];
        }
        }
    }
    }

    switch(codificacao){
        case BINARIA:
        {   mensagem = receptora.ReceptoraBinaria(fluxoBrutoDeBits);
            MensagemRecebida(mensagem);
            break;
        }
        case MANCHESTER:
        {   mensagem = receptora.ReceptoraManchester(fluxoBrutoDeBits);
            MensagemRecebida(mensagem);
            break;
        }
        case BIPOLAR:
        {   
            mensagem = receptora.ReceptoraBipolar(fluxoBrutoDeBits);
            MensagemRecebida(mensagem);
            break;
        }
    }

}

void CamadaAplicacao::MensagemCodificada(){
    cout << "A mensagem codificada pode ser representada por: " << endl;
}

void CamadaAplicacao::MensagemRecebida(string mensagem){
    cout << "\nA mensagem recebida foi: " << mensagem;
}

vector <int> MeioDeComunicacao::Comunicacao(vector <int> fluxoBrutoDeBits){
    vector <int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
    for(int i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++){
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);       
    }
    return fluxoBrutoDeBitsPontoB;
}
