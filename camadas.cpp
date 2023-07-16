// #include <vector>
// #include <iostream>
// using namespace std;
// void CamadaEnlaceDadosTransmissora(int quadro[]){
//     CamadaEnlaceDadosTransmissoraEnquadramento(quadro);
//     CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
//     CamadaFisicaTransmissora(quadro);
// }

// void CamadaEnlaceDadosTransmissoraEnquadramento(int quadro[]){
//     int tipoDeEnquadramento = 0;
//     vector <int> quadroEnquadrado;
//     switch(tipoDeEnquadramento){
//         case 0: //contagem de caracteres
//             quadroEnquadrado = 
//             CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);
//             break;
//         case 1:
//             quadroEnquadrado = camadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
//             break;

//     }
// }
// void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[]){
//     int tipoDeControleDeErro = 0;
//     switch(tipoDeControleDeErro){
//         case 0: //bit de paridade par
//         case 1: //CRC
//     }
// }
// void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[]){
    
// }
// void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]){
//     //USAR POLINOMIO CRC-32(IEEE 802)
// }
// void  CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[]){

// }
// void camadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int quadro[]){

// }

// //recepcao
// void CamadaEnlaceDadosReceptora(int quadro[]){
//     CamadaEnlaceDadosReceptoraEnquadramento(quadro);
//     CamadaEnlaceDadosReceptoraControleDeErro(quadro);
//     CamadaAplicacaoReceptora(quadro);
// }
// void CamadaEnlaceDadosReceptoraEnquadramento(int quadro[]){
//      int tipoDeEnquadramento = 0;
//     vector <int> quadroDesenquadrado;
//     switch(tipoDeEnquadramento){
//         case 0: //contagem de caracteres
//             quadroDesenquadrado = 
//             CamadaEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);
//             break;
//         case 1:
//             quadroDesenquadrado = camadaEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
//             break;

//     }
// }
// void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[]){
//     int tipoDeControleDeErro = 0;
//     switch(tipoDeControleDeErro){
//         case 0: //bit de paridade par
//         break;
//         case 1: //CRC
//         break;
//     }
// }
// void  CamadaEnlaceReceptoraEnquadramentoContagemDeCaracteres(int quadro[]){

// }
// void camadaEnlaceReceptoraEnquadramentoInsercaoDeBytes(int quadro[]){

// }
// void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]){
    
// }
// void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]){
//     //USAR POLINOMIO CRC-32(IEEE 802)
// }

// void Comunicacao(vector <int> fluxoBrutoDeBits) {
//     vector <int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
//     int erro, porcentagemDeErros;
//     porcentagemDeErros = 0; //10%, 20%, 30%...
//     fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
//     while(fluxoBrutoDeBitsPontoA.size() != fluxoBrutoDeBitsPontoA.size()){
//         if((rand()%100)==) ///probabilidade do erro
//         fluxoBrutoDeBitsPontoB+= fluxoBrutoDeBitsPontoA;
//         else //ERRO! INVERTER(USA CONDICAO TERNARIA)
//         fluxoBrutoDeBitsPontoB==0) ?
//         fluxoBrutoDeBitsPontoA= fluxoBrutoDeBitsPontoB++:
//         fluxoBrutoDeBitsPontoA=fluxoBrutoDeBitsPontoB--;
//     }
// }
