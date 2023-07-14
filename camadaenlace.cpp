#include "camadaenlace.hpp"
vector <int> CamadaEnlace::int_byte(int size){
    vector <int> byte;
    for(int i = 0; i <= 7; i++){
        byte.push_back(size % 2);
        size = size/2;
    }
    return byte;
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
