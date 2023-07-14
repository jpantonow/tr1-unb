#include "camadaenlace.hpp"
vector <int> CamadaEnlace::int_byte(int size){
    vector <int> byte;
    for(int i = 0; i <= 7; i++){
        byte.push_back(size % 2);
        size = size/2;
    }
    return byte;
}
vector <int> CamadaEnlace::complementode1(vector <int> numero){
    vector<int> complemento;
    for(int i = 0; i < numero.size(); i++){
        if(numero[i] == 1){
            complemento.push_back(0);
        }
        else{
            complemento.push_back(1);
        }
    }
    return complemento;
}
vector <int> CamadaEnlace::somabinaria(vector <int> numero1, vector<int> numero2){
    int carry = 0;
    int soma = 0;
    vector <int> resultado;
    for(int i = numero1.size(); i >= 0; i--){
        int soma = numero1[i] + numero2[i] + carry;
        resultado[i] = soma % 2;
        carry = soma/2;
    }
    if(carry!=0){
        resultado.insert(resultado.begin(), carry);
    }
    return resultado;
}
vector <int> CamadaEnlaceTransmissora::ContagemDeCaracteres(vector <int> quadro){
int cont = 0;
vector <int> enquadrado;
int size = quadro.size();
vector <int> byte = int_byte(size);
for(int i = 0; i < byte.size(); i++){
    enquadrado.insert(enquadrado.begin() + i, byte[i]);
}
return enquadrado;
}
vector <int> CamadaEnlace::inserir_bytes(vector <int> byte, vector<int> quadro){
    for(int i = 0; i < byte.size(); i++){
        quadro.push_back(byte[i]);
    }
    return quadro;
}
vector <int> CamadaEnlaceTransmissora::InsercaoDeBytes(vector <int> quadro){
//bit de flag = 01111110
int cont = 0;
int um5vezes = 0;
vector <int> enquadrado;

while(!quadro.empty()){
    if(cont==0){
        inserir_bytes(esc, enquadrado);
        inserir_bytes(flag, enquadrado);
    }
    if(cont==7){
        cont = 0;
        enquadrado.push_back(quadro[0]);
        quadro.pop_back();
        inserir_bytes(esc, enquadrado);
        inserir_bytes(flag, enquadrado);
        continue;
    }
    cont +=1;
    enquadrado.push_back(quadro[0]);
    quadro.pop_back();
}
return enquadrado;
}
vector <int> CamadaEnlace::dividirquadro(vector <int> quadro){
    int partes = quadro.size()/8;
    vector<int> divisao;
    vector<vector <int>> resultado;
    while(partes!=0){
        divisao = inserir_bytes(quadro, divisao);
        resultado.push_back(divisao);
    }
}
vector <int> CamadaEnlace::checksum(vector <int> byte){
    vector <int> checksum;
}
vector <int> CamadaEnlaceTransmissora::ControleDeErroCRC(vector <int> quadro){
// 802.3 POLINOMIO GERADOR
}

vector <int> CamadaEnlaceTransmissora::ControleDeErroBitParidadePar(vector <int> quadro){

}

int CamadaEnlaceReceptora::ContagemDeCaracteres(vector <int> quadro){

}
vector <int> CamadaEnlaceReceptora::InsercaoDeBytes(vector <int> quadro){

}
vector <int> CamadaEnlaceReceptora::InsercaoDeBytes(vector <int> quadro){

}
vector <int> CamadaEnlaceReceptora::InsercaoDeBytes(vector <int> quadro){

}
