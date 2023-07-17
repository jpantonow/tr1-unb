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
 for(int i = 0; i < divisao.size(); i++){
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
    // if(quadro[0]==1){
    //     um5vezes +=1;
    // }
    // else{
    //     um5vezes = 0;
    // }
    // if(um5vezes == 5){
    //     quadro.insert(quadro.begin()+1,0);
    // }
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
// while(enquadrado.size() % 8 != 0){
//     enquadrado.push_back(0);
// }
return enquadrado;
}
vector <int> CamadaEnlaceReceptora::InsercaoDeBytes(vector <int> quadro){
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
    vector<vector <int>> resultado;
    vector<int> byte;
    int loop = quadro.size()/8;
    for(int j = 0; j < loop; j++){
        for(int i = 0; i < 8; i++){
            byte.push_back(quadro[0]);
            quadro.erase(quadro.begin());
            continue;
        }
        resultado.push_back(byte); 
        byte.clear();
        continue;
    }
    return resultado;
}
vector <int> CamadaEnlaceTransmissora::iniciar(int erro, int enquadramento, vector<int> tremdebits){
    vector <int> corrigido;
    vector <int> enquadrado;
    getchar();
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
            desenquadrado = InsercaoDeBytes(corrigido);
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
    vector <int> controledeerro;
    controledeerro = calculoparidade(tremdebits);
    return controledeerro;
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
    int tam = tremdebits.size();
    for(int i = tremdebits.size()-1; i > tam-9; i--){
        paridade_recebida.insert(paridade_recebida.begin(),tremdebits[i]);
        tremdebits.pop_back();
    }
    vector <int> carga_util;
    cout << "carga util:" << endl;
    for(int i = 8; i < tam-8; i++){
        cout << tremdebits[i];
        carga_util.push_back(tremdebits[i]);
    }
cout <<"\n";
    vector <int> calcularparidade; 
    calcularparidade = calculoparidade(carga_util);
    int tam2 = calcularparidade.size();
    for(int i = tam2-1; i > tam2-9; i--){
         paridade_calculada.insert(paridade_calculada.begin(),calcularparidade[i]);
         calcularparidade.pop_back();
    }
    if(paridade_calculada!=paridade_recebida){
        cout << "tamanho da paridade calculada: " << paridade_calculada.size() << endl; getchar();
        cout << "tamanho da paridade recebida: " << paridade_recebida.size() << endl; getchar();
        aux = 1;
    }

    if (aux) {
        cout << "Erro detectado no quadro!!!" << endl;
    }
    cout << "paridade calculada: " << endl;
    for(int i = 0; i < paridade_calculada.size(); i++){
        cout << paridade_calculada[i];
    }
    cout << "\n";
    getchar();
    cout << "paridade recebida: " << endl;
    for(int i = 0; i < paridade_recebida.size(); i++){
        cout << paridade_recebida[i];
    }
    getchar();
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

