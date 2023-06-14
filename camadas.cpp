#include "camadafisica.hpp"
#include <bitset>
vector <int> CamadaFisicaTransmissora::CodificarBinario(string mensagem){
for(int i = 0; i < mensagem.size(); i++){
    char caractere = mensagem[i];
    bitset<8> binary(caractere);
    for(int j = 0; j <= 7; i++){
        int bit = binary[j];
        quadro.push_back(bit);
    }
}
return quadro;
}
void CamadaAplicacao::Transmissora(vector <int> quadro){
cout << "Escolha uma mensagem a ser codificada: " << endl;
cin >> mensagem;
cout << "Escolha um tipo de codificacao a ser utilizada: " << endl;
cin >> codificacao;
CamadaFisicaTransmissora camadaFisicaTransmissora;
camadaFisicaTransmissora.iniciar(codificacao,mensagem);
}

void CamadaAplicacao::Receptora(vector <int> quadro){

}
void CamadaAplicacao::Mensagem(string mensagem){

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