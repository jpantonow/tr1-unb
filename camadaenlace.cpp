#include "camadaenlace.hpp"
vector <int> CamadaEnlace::int_byte(int size){
    vector <int> byte;
    for(int i = 0; i <= 7; i++){
        byte.insert(byte.begin(),(size % 2));
        size = size/2;
    }
    return byte;
}

vector <int> CamadaEnlaceTransmissora::ContagemDeCaracteres(vector <int> quadro){
vector <int> enquadrado;
vector <vector <int>> divisao;
divisao = dividirquadro(quadro);
 int size = divisao.size();
 vector <int> byte = int_byte(size);
 enquadrado = inserir_bytes(byte,enquadrado);
 for(int i = 0; i < divisao.size()-(i*size); i++){
    for(int j = 0; j < divisao[i].size(); j++){
        enquadrado.push_back(divisao[i][j]);
     }
 }
return enquadrado;
}

vector <int> CamadaEnlaceReceptora::ContagemDeCaracteres(vector <int> quadro){
vector <int> enquadrado;
vector <vector <int>> divisao;
divisao = dividirquadro(quadro);
 int size = divisao.size();
 vector <int> byte = int_byte(size-1);
 if(byte!=divisao[0]){
    cout <<"\n" << "Erro na contagem de caracteres" << endl;
 }

 for(int i = 0; i < byte.size(); i++){
     enquadrado.insert(enquadrado.begin() + i, byte[i]);
     for(int j = 0; j < divisao[i].size(); j++){
        enquadrado.push_back(divisao[i][j]);
     }
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
int cont = 0;
int um5vezes = 0;
vector <int> enquadrado;

while(!quadro.empty()){
    if(cont==0){
        inserir_bytes(enquadrado, esc);
        inserir_bytes(enquadrado, flag);
    }
    if(cont==7){
        cont = 0;
        enquadrado.push_back(quadro[0]);
        quadro.erase(quadro.begin());
        inserir_bytes(enquadrado, esc);
        inserir_bytes(enquadrado, flag);
        continue;
    }
    cont +=1;
    enquadrado.push_back(quadro[0]);
    quadro.erase(quadro.begin());
}
return enquadrado;
}
vector <vector<int>> CamadaEnlace::dividirquadro(vector <int> quadro){
    int partes = quadro.size()/8;
    vector<int> divisao;
    vector<vector <int>> resultado;
    while(partes!=0){
        divisao = inserir_bytes(divisao, quadro);
        resultado.push_back(divisao);
        partes = partes - 1;
    }
    return resultado;
}
vector <int> CamadaEnlaceTransmissora::iniciar(int erro, int enquadramento, vector<int> tremdebits){
    vector <int> corrigido;
    vector <int> enquadrado;
    switch(erro){
        case PARIDADE:
            corrigido = ControleDeErroBitParidadePar(tremdebits);
            break;
        case CRC:
            corrigido = ControleDeErroCRC(tremdebits);
            break;
        case HAMMING:
            corrigido = codificacaoHamming(tremdebits);
            break;
    }
    switch(enquadramento){
        case CONTAGEM:
            enquadrado = ContagemDeCaracteres(corrigido);
            break;
        case INSERCAO:
            enquadrado = InsercaoDeBytes(corrigido);
            break;
    }
    return enquadrado;
}
vector <int> CamadaEnlaceReceptora::iniciar(int erro, int enquadramento, vector<int> tremdebits){
    vector <int> corrigido;
    vector <int> desenquadrado;
    switch(erro){
        case PARIDADE:
            corrigido = ControleDeErroBitParidadePar(tremdebits);
            break;
        case CRC:
            corrigido = ControleDeErroCRC(tremdebits);
            break;
        case HAMMING:
            corrigido = decodificacaoHamming(tremdebits);
            break;
    }
    switch(enquadramento){
        case CONTAGEM:
            desenquadrado = ContagemDeCaracteres(corrigido);
            break;
        case INSERCAO:
            //desenquadrado = InsercaoDeBytes(corrigido);
            break;
    }
    return desenquadrado;
}
vector <int> CamadaEnlaceTransmissora::codificacaoHamming(vector <int> tremdebits) {
    int par0, par1, par2, par3;
    vector <int> tremcodificado;

    par0 = tremdebits[0] ^ tremdebits[1] ^ tremdebits[3] ^ tremdebits[4] ^ tremdebits[6];
    par1 = tremdebits[0] ^ tremdebits[2] ^ tremdebits[3] ^ tremdebits[5] ^ tremdebits[6];
    par2 = tremdebits[1] ^ tremdebits[2] ^ tremdebits[3] ^ tremdebits[7];
    par3 = tremdebits[4] ^ tremdebits[5] ^ tremdebits[6] ^ tremdebits[7];

    tremcodificado = {par0, par1, tremdebits[0], par2, tremdebits[1], tremdebits[2], tremdebits[3], par3, tremdebits[4], tremdebits[5], tremdebits[6], tremdebits[7], 0, 0, 0, 0};

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

// vector <int> CamadaEnlaceTransmissora::ControleDeErroBitParidadePar(vector <int> tremdebits) {
//     int bit_paridade{};

//     for (int i{}; i < tremdebits.size(); i++) {
//         bit_paridade = bit_paridade ^ tremdebits[i];
//     }

//     tremdebits.push_back(bit_paridade);

//     return tremdebits;
// }

vector <int> CamadaEnlaceTransmissora::ControleDeErroBitParidadePar(vector <int> tremdebits){
    tremdebits = calculoparidade(tremdebits);
    return tremdebits;
}

vector <int> CamadaEnlace::calculoparidade(vector <int> tremdebits){
    vector <vector <int>> divisao;
    divisao = dividirquadro(tremdebits);
    int bit_paridade = 0;
     int sizeofbyte = divisao[0].size();
    for(int i = 0; i < sizeofbyte; i++){
        for(int j = 0; j < divisao.size(); j++){
            bit_paridade = bit_paridade ^ divisao[j][i];
        }
        tremdebits.push_back(bit_paridade);
        bit_paridade = 0;
    }
    return tremdebits;
}
vector <int> CamadaEnlaceReceptora::ControleDeErroBitParidadePar(vector <int> tremdebits) {
    int aux{};
    vector <int> paridade_recebida;
    vector <int> paridade_calculada;
    for(int i = tremdebits.size(); i > tremdebits.size()-9; i--){
        paridade_recebida.insert(paridade_recebida.begin(),tremdebits[i]);
        tremdebits.pop_back();
    }
    paridade_calculada = calculoparidade(tremdebits);
    for(int i = 0; i < paridade_calculada.size(); i++){
        if(paridade_calculada[i]!= paridade_recebida[i]){
            aux = 1;
        }
    }

    if (aux) {
        cout << "Erro detectado no quadro!!!" << endl;
    }

    //tremdebits.pop_back();

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
             cout << "Erro encontrado!!!" << endl;
        }
    }

    tremdebits.clear();

    for (int k{}; k < dividendo.size() - 32; k++){
        tremdebits.push_back(dividendo[k]);
    }

    return tremdebits;
}

