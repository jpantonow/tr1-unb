#include "camadaenlace.hpp"

//vector <int> CamadaEnlace::complementode1(vector <int> numero){
//     vector<int> complemento;
//     for(int i = 0; i < numero.size(); i++){
//         if(numero[i] == 1){
//             complemento.push_back(0);
//         }
//         else{
//             complemento.push_back(1);
//         }
//     }
//     return complemento;
// }
// vector <int> CamadaEnlace::somabinaria(vector <int> numero1, vector<int> numero2){
//     int carry = 0;
//     int soma = 0;
//     vector <int> resultado;
//     for(int i = numero1.size(); i >= 0; i--){
//         int soma = numero1[i] + numero2[i] + carry;
//         resultado[i] = soma % 2;
//         carry = soma/2;
//     }
//     if(carry!=0){
//         resultado.insert(resultado.begin(), carry);
//     }
//     return resultado;
// }

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
//vector <int> enquadrado;
//quadro = dividirquadro(quadro);
// int size = quadro.size();
// vector <int> byte = int_byte(size);
// for(int i = 0; i < byte.size(); i++){
//     enquadrado.insert(enquadrado.begin() + i, byte[i]);
// }
// return enquadrado;
vector <vector <int>> enquadrado;
enquadrado.push_back(quadro);
vector <int> cabecalho = int_byte(enquadrado.size());
enquadrado.insert(enquadrado.begin(), cabecalho);

}
vector <int> CamadaEnlace::inserir_bytes(vector <int> byte, vector<int> quadro){
    for(int i = 0; i < byte.size(); i++){
        quadro.push_back(byte[i]);
    }
    return quadro;
}
vector <int> CamadaEnlaceTransmissora::InsercaoDeBytes(vector <int> quadro){
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
vector <vector<int>> CamadaEnlace::dividirquadro(vector <int> quadro){
    int partes = quadro.size()/8;
    vector<int> divisao;
    vector<vector <int>> resultado;
    while(partes!=0){
        divisao = inserir_bytes(quadro, divisao);
        resultado.push_back(divisao);
    }
    return resultado;
}


vector <int> CamadaEnlaceTransmissora::codificacaoHamming(vector <int> tremdebits) {
    int par0, par1, par2, par3;
    vector <int> tremcodificado;

    par0 = tremdebits[0] ^ tremdebits[1] ^ tremdebits[3] ^ tremdebits[4] ^ tremdebits[6];
    par1 = tremdebits[0] ^ tremdebits[2] ^ tremdebits[3] ^ tremdebits[5] ^ tremdebits[6];
    par2 = tremdebits[1] ^ tremdebits[2] ^ tremdebits[3] ^ tremdebits[7];
    par3 = tremdebits[4] ^ tremdebits[5] ^ tremdebits[6] ^ tremdebits[7];

    tremcodificado = {par0, par1, tremdebits[0], par2, tremdebits[1], tremdebits[2], tremdebits[3], par3, tremdebits[4], tremdebits[5], tremdebits[6], tremdebits[7]};

    return tremcodificado;
}

vector <int> CamadaEnlaceReceptora::decodificacaoHamming(vector <int> tremdebits) {
    int pos_errada {};
    vector <int> tremcorrigido;

    pos_errada = 1 * (tremdebits[0] ^ tremdebits[2] ^ tremdebits[4] ^ tremdebits[6] ^ tremdebits[8] ^ tremdebits[10]) + 2 * (tremdebits[1] ^ tremdebits[2] ^ tremdebits[5] ^ tremdebits[6] ^ tremdebits[9] ^ tremdebits[10]) + 4 * (tremdebits[3] ^ tremdebits[4] ^ tremdebits[5] ^ tremdebits[6] ^ tremdebits[11]) + 8 * (tremdebits[7] ^ tremdebits[8] ^ tremdebits[9] ^ tremdebits[10] ^ tremdebits[11]);

    if (pos_errada) {
        if (tremdebits[pos_errada - 1]) {
            tremdebits[pos_errada - 1] = 0;
        } else {
            tremdebits[pos_errada] = 1;
        }
    }

    tremcorrigido = {tremdebits[2], tremdebits[4], tremdebits[5], tremdebits[6], tremdebits[8], tremdebits[9], tremdebits[10], tremdebits[11]};

    return tremcorrigido;

}

vector <int> CamadaEnlaceTransmissora::ControleDeErroBitParidadePar(vector <int> tremdebits) {
    int bit_paridade{};

    for (int i{}; i < tremdebits.size(); i++) {
        bit_paridade = bit_paridade ^ tremdebits[i];
    }

    tremdebits.push_back(bit_paridade);

    return tremdebits;
}

vector <int> CamadaEnlaceReceptora::ControleDeErroBitParidadePar(vector <int> tremdebits) {
    int aux{};

    for (int i{}; i < tremdebits.size(); i++) {
        aux = aux ^ tremdebits[i];
    }

    if (aux) {
        cout << "Erro detectado no quadro!!!" << "\n";
    }

    tremdebits.pop_back();

    return tremdebits;
}

vector <int> CamadaEnlaceTransmissora::ControleDeErroCRC(vector <int> tremdebits) {
    vector <int> aux1, aux2, dividendo;

    for (int i{}; i < tremdebits.size(); i++) {
        dividendo.push_back(tremdebits[i]);
    }

    for (int i{}; i < 32; i++) {
        dividendo.push_back(0);
        aux1.push_back(dividendo[i]);
    }

    for (int i{}; i < tremdebits.size(); i++){
        aux1.push_back(dividendo[crc.size() + i]);
        for (int j{}; j < crc.size(); j++) {
            if (aux1[0]) {
                aux2.push_back(aux1[j] ^ crc[j]);
            } else {
                aux2.push_back(aux1[j] ^ 0);
            }
        }
        aux1.clear();
        for (int j=1; j < aux2.size(); j++) {
            aux1.push_back(aux2[j]);
        }
        aux2.clear();
    }

    for (int k{}; k < aux1.size(); k++) {
        tremdebits.push_back(aux1[k]);
    }
    return tremdebits;
}

vector <int> CamadaEnlaceReceptora::ControleDeErroCRC(vector <int> tremdebits) {
    vector <int> aux1, aux2, dividendo;

    for (int i{}; i < tremdebits.size(); i++) {
        dividendo.push_back(tremdebits[i]);
    }

    for (int i{}; i < 32; i++) {
        aux1.push_back(dividendo[i]);
    }

    for (int i{}; i < tremdebits.size() - 32; i++){
        aux1.push_back(dividendo[crc.size() + i - 1]);

        for (int j{}; j < crc.size(); j++) {
            if (aux1[0]) {
                aux2.push_back(aux1[j] ^ crc[j]);
            } else {
                aux2.push_back(aux1[j] ^ 0);
            }
        }
        aux1.clear();
        for (int j=1; j < aux2.size(); j++) {
            aux1.push_back(aux2[j]);
        }
        aux2.clear();
    }

    for (int k{}; k < aux1.size(); k++){
        if (aux1[k]) {
             cout << "Erro encontrado!!!";
        }
    }

    tremdebits.clear();

    for (int k{}; k < dividendo.size() - 32; k++){
        tremdebits.push_back(dividendo[k]);
    }

    return tremdebits;
}

