#include "camadafisica.hpp"
#include <bitset>
vector <int> CamadaAplicacao::CodificarBinario(string mensagem, vector <int> &quadro){
for(int i = mensagem.size()-1; i >= 0; i--){
    char caractere = mensagem[i];
    bitset<8> binary(caractere);
    for(int j = 7; j = 0; i--){
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
camadaFisicaTransmissora.iniciar(codificacao);
}

void CamadaAplicacao::Receptora(vector <int> quadro){

}
void CamadaAplicacao::Mensagem(string mensagem){

}

void CamadaFisicaTransmissora::iniciar(int codificacao){
switch(codificacao){
    case 0:
            fluxoBrutoDeBits = TransmissoraBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = TransmissoraManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = TransmissoraBipolar(quadro);
            break;
}
}
vector <int> CamadaFisicaTransmissora::TransmissoraBinaria(vector <int> quadro){

}
vector <int> CamadaFisicaTransmissora::TransmissoraManchester(vector <int> quadro){

}
vector <int> CamadaFisicaTransmissora::TransmissoraBipolar(vector <int> quadro){

}