#include "camadafisica.hpp"
#include <bitset>
vector <int> CamadaFisicaTransmissora::CodificarBinario(string mensagem){
for(int i = 0; i < mensagem.size(); i++){
    char caractere = mensagem[i];
    int b = int(caractere);
    bitset<sizeof(b) * 8> bits(b);
    quadro.push_back(b);
    }
    return quadro;
}

void CamadaAplicacao::Transmissora(){
cout << "Escolha uma mensagem a ser codificada: " << endl;
cin >> mensagem;
cout << "Escolha um tipo de codificacao a ser utilizada: " << endl;
cin >> codificacao;
CamadaFisicaTransmissora camadaFisicaTransmissora;
camadaFisicaTransmissora.iniciar(codificacao,mensagem);
}

void CamadaFisicaTransmissora::iniciar(int codificacao, string mensagem){

switch(codificacao){
    case BINARIA:
            quadro = CodificarBinario(mensagem);
            fluxoBrutoDeBits = TransmissoraBinaria(quadro);
            break;
        case MANCHESTER:
            fluxoBrutoDeBits = TransmissoraManchester(quadro);
            break;
        case BIPOLAR:
            fluxoBrutoDeBits = TransmissoraBipolar(quadro);
            break;
}
CamadaAplicacao camadaAplicacao;
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
        cout << fluxoBrutoDeBits[i];
    }
}

void CamadaAplicacao::Mensagem(){
    cout << "O codigo codificado pode ser representado por: " << endl;
}