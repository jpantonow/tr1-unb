// #include "camadafisica.hpp"
// #include <iostream>
// #include <string>
// #include <cmath>
// #include <vector>
// using namespace std;

// void main(){
//     AplicacaoTransmissora();
// }

// void AplicacaoTransmissora(){
//     string mensagem;
//     cout << "Digite uma mensagem:" << endl;
//     cin >> mensagem;

//     CamadaDeAplicacaoTransmissora(mensagem);
// }

// void CamadaDeAplicacaoTransmissora(string mensagem){
//     CamadaFisicaTransmissora(quadro);
// }

// void CamadaFisicaTransmissora(int quadro[]){
//     int codificacao;
//     int fluxoBrutoDeBits [];
//     switch(codificacao){
//     case 0:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraBinaria(quadro);
//             break;
//         case 1:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraManchester(quadro);
//             break;
//         case 2:
//             fluxoBrutoDeBits = CamadaFisicaTransmissoraBipolar(quadro);
//             break;
// }
// CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
// }

// int CamadaFisicaTransmissoraBinaria(){

// }
// int CamadaFisicaTransmissoraManchester(){

// }
// int CamadaFisicaTransmissoraBipolar(){

// }

// void MeioDeComunicacao(int fluxoBrutoDeBits){
//     int fluxoBrutoDeBitsPontoA[], fluxoBrutoDeBitsPontoB[];
//     fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
//     while(fluxoBrutoDeBitsPontoB.length() != fluxoBrutoDeBitsPontoa){
//         fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA;
//     }
//     CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
// }

// void CamadaFisicaReceptora(int quadro){
//     int codificacao = 0;
//     int fluxoBrutoDeBits[];
//     switch(codificacao){
//         case 0:
//         fluxoBrutoDeBits = CamadaFisicaReceptoraBinaria(quadro);
//         break;
//         case 1:
//         fluxoBrutoDeBits = CamadaFisicaReceptoraManchester(quadro);
//         break;
//         case 2:
//         fluxoBrutoDeBits = CamadaFisicaReceptoraBipolar(quadro);
//         break;
//     }
//     CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
// }
// int CamadaFisicaReceptoraBinaria(int quadro){

// }
// int CamadaFisicaReceptoraManchester(int quadro){
// }
// int CamadaFisicaReceptoraBipolar(int quadro){}

// void CamadaDeAplicacaoReceptora(int quadro){
//     AplicacaoReceptora(mensagem);
// }
// void AplicacaoReceptora(string mensagem){
//     cout << "A mensagem recebida foi:" << mensagem << endl;
// }