#include "camadaenlace.hpp"

int CamadaEnlaceTransmissora::ContagemDeCaracteres(vector <int> quadro){
int cont = quadro.size();
return cont;
}

vector <int> CamadaEnlaceTransmissora::InsercaoDeBytes(vector <int> quadro){
int cont = 0;
vector <int> enquadrado;
while(!quadro.empty()){
    if(cont==0){
        enquadrado.push_back(0);
        enquadrado.push_back(0);
        enquadrado.push_back(0);
        enquadrado.push_back(0);
        enquadrado.push_back(1);
        enquadrado.push_back(0);
        enquadrado.push_back(0);
        enquadrado.push_back(0);
    }
    if(cont==7){
        cont = 0;
        enquadrado.push_back(quadro[0]);
        quadro.pop_back();
    }
    cont +=1;
    enquadrado.push_back(quadro[0]);
    quadro.pop_back();
}
return enquadrado;
}
vector <int> CamadaEnlaceTransmissora::ControleDeErroCRC(vector <int> quadro){

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
