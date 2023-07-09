#include <vector>
#include <iostream>
using namespace std;
void CamadaEnlaceDadosTransmissora(int quadro[]){
    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
    CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
    CamadaFisicaTransmissora(quadro);
}

void CamadaEnlaceDadosTransmissoraEnquadramento(int quadro[]){
    int tipoDeEnquadramento = 0;
    vector <int> quadroEnquadrado;
    switch(tipoDeEnquadramento){
        case 0: //contagem de caracteres
            quadroEnquadrado = 
            CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroEnquadrado = camadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;

    }
}
void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]){

}
void  CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[]){

}
void camadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int quadro[]){

}

//recepcao
void CamadaEnlaceDadosReceptora(int quadro[]){
    CamadaEnlaceDadosReceptoraEnquadramento(quadro);
    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
    CamadaAplicacaoReceptora(quadro);
}
void CamadaEnlaceDadosReceptoraEnquadramento(int quadro[]){
     int tipoDeEnquadramento = 0;
    vector <int> quadroDesenquadrado;
    switch(tipoDeEnquadramento){
        case 0: //contagem de caracteres
            quadroDesenquadrado = 
            CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);
            break;
        case 1:
            quadroDesenquadrado = camadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
            break;

    }
}
void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[]){
}
void  CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(int quadro[]){

}
void camadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(int quadro[]){

}
