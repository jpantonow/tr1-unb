#include "camadaenlace.hpp"
vector <int> CamadaEnlace::int_byte(int size){
    vector <int> byte;
    for(int i = 0; i <= 7; i++){
        byte.insert(byte.begin(),(size % 2));
        size = size/2;
    }
    return byte;
}
/**
 * @brief Método de enquadramento que adiciona um byte de cabeçalho para ler a carga útil.
 * 
 * @param quadro 
 * @return vector <int> 
 */
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
/**
 * @brief Método de desenquadramento que retira o cabeçalho para ler a carga útil.
 * 
 * @param quadro 
 * @return vector <int> 
 */
vector <int> CamadaEnlaceReceptora::ContagemDeCaracteres(vector <int> quadro){
vector <int> desenquadrado;
vector <vector <int>> divisao;
divisao = dividirquadro(quadro);
int size = divisao.size();
vector <int> byte = int_byte(size-1);


for(int i = 8; i < quadro.size(); i++){
    desenquadrado.push_back(quadro[i]);
}
return desenquadrado;
}

vector <int> CamadaEnlace::inserir_bytes(vector <int> byte, vector<int> quadro){
    for(int i = 0; i < byte.size(); i++){
        quadro.push_back(byte[i]);
    }
    return quadro;
}
// vector <int> CamadaEnlaceTransmissora::InsercaoDeBytes(vector <int> quadro){
// int cont = 0;
// int um5vezes = 0;
// vector <int> enquadrado;

// while(!quadro.empty()){
//     // if(quadro[0]==1){
//     //     um5vezes +=1;
//     // }
//     // else{
//     //     um5vezes = 0;
//     // }
//     // if(um5vezes == 5){
//     //     quadro.insert(quadro.begin()+1,0);
//     // }
//     if(cont==0){
//         inserir_bytes(enquadrado, esc);
//         inserir_bytes(enquadrado, flag);
//     }
//     if(cont==7){
//         cont = 0;
//         enquadrado.push_back(quadro[0]);
//         quadro.erase(quadro.begin());
//         inserir_bytes(enquadrado, esc);
//         inserir_bytes(enquadrado, flag);
//         continue;
//     }
//     cont +=1;
//     enquadrado.push_back(quadro[0]);
//     quadro.erase(quadro.begin());
// }
// // while(enquadrado.size() % 8 != 0){
// //     enquadrado.push_back(0);
// // }
// return enquadrado;
// }
// vector <int> CamadaEnlaceReceptora::InsercaoDeBytes(vector <int> quadro){
// int cont = 0;
// int um5vezes = 0;
// vector <int> enquadrado;

// while(!quadro.empty()){
//     if(cont==0){
//         inserir_bytes(enquadrado, esc);
//         inserir_bytes(enquadrado, flag);
//     }
//     if(cont==7){
//         cont = 0;
//         enquadrado.push_back(quadro[0]);
//         quadro.erase(quadro.begin());
//         inserir_bytes(enquadrado, esc);
//         inserir_bytes(enquadrado, flag);
//         continue;
//     }
//     cont +=1;
//     enquadrado.push_back(quadro[0]);
//     quadro.erase(quadro.begin());
// }
// return enquadrado;
// }
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
vector <vector<int>> CamadaEnlace::dividirhamming(vector <int> quadro){
    vector<vector <int>> resultado;
    vector<int> byte;
    int loop = quadro.size()/16;
    for(int j = 0; j < loop; j++){
        for(int i = 0; i < 16; i++){
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
    switch(enquadramento){
        case CONTAGEM:
            desenquadrado = ContagemDeCaracteres(tremdebits);
            break;
        case INSERCAO:
            desenquadrado = InsercaoDeBytes(tremdebits);
            break;
    }
    switch(erro){
        case PARIDADE:
            corrigido = ControleDeErroBitParidadePar(desenquadrado);
            break;
        case CRC:
            corrigido = ControleDeErroCRC(desenquadrado);
            break;
        case HAMMING:
            corrigido = decodificacaoHamming(desenquadrado);
            break;
    }
    return corrigido;
}
vector <int> CamadaEnlaceTransmissora::codificacaoHamming(vector <int> binary) {
    int par0, par1, par2, par3;
    vector <int> tremcodificado;
    vector <vector<int>> tremdebits;
    tremdebits = dividirquadro(binary);
    vector <vector<int>> resultado;
    vector <int> corrigido;
    for(int i = 0; i < tremdebits.size(); i++){
        par0 = tremdebits[i][0] ^ tremdebits[i][1] ^ tremdebits[i][3] ^ tremdebits[i][4] ^ tremdebits[i][6];
        par1 = tremdebits[i][0] ^ tremdebits[i][2] ^ tremdebits[i][3] ^ tremdebits[i][5] ^ tremdebits[i][6];
        par2 = tremdebits[i][1] ^ tremdebits[i][2] ^ tremdebits[i][3] ^ tremdebits[i][7];
        par3 = tremdebits[i][4] ^ tremdebits[i][5] ^ tremdebits[i][6] ^ tremdebits[i][7];
        tremcodificado = {par0, par1, tremdebits[i][0], par2, tremdebits[i][1], tremdebits[i][2], tremdebits[i][3], par3, tremdebits[i][4], tremdebits[i][5], tremdebits[i][6], tremdebits[i][7], 0, 0, 0, 0};
        resultado.push_back(tremcodificado);
        tremcodificado.clear();
    }
    // par0 = tremdebits[0] ^ tremdebits[1] ^ tremdebits[3] ^ tremdebits[4] ^ tremdebits[6];
    // par1 = tremdebits[0] ^ tremdebits[2] ^ tremdebits[3] ^ tremdebits[5] ^ tremdebits[6];
    // par2 = tremdebits[1] ^ tremdebits[2] ^ tremdebits[3] ^ tremdebits[7];
    // par3 = tremdebits[4] ^ tremdebits[5] ^ tremdebits[6] ^ tremdebits[7];
    for(int i =0; i < resultado.size();i++){
        for(int j = 0; j < resultado[i].size();j++){
            corrigido.push_back(resultado[i][j]);
        }
    }
    return corrigido;
}
vector <int> CamadaEnlaceReceptora::decodificacaoHamming(vector <int> binary) {
    int pos_errada= 0;
    vector <int> tremcorrigido;
    vector <vector<int>> tremdebits;
    tremdebits = dividirhamming(binary);
    vector <vector<int>> resultado;
    vector <int> corrigido;
    bool haserror;

   for(int i = 0; i < tremdebits.size(); i++){
        pos_errada = 1 * (tremdebits[i][0] ^ tremdebits[i][2] ^ tremdebits[i][4] ^ tremdebits[i][6] ^ tremdebits[i][8] ^ tremdebits[i][10]) + 2 * (tremdebits[i][1] ^ tremdebits[i][2] ^ tremdebits[i][5] ^ tremdebits[i][6] ^ tremdebits[i][9] ^ tremdebits[i][10]) + 4 * (tremdebits[i][3] ^ tremdebits[i][4] ^ tremdebits[i][5] ^ tremdebits[i][6] ^ tremdebits[i][11]) + 8 * (tremdebits[i][7] ^ tremdebits[i][8] ^ tremdebits[i][9] ^ tremdebits[i][10] ^ tremdebits[i][11]);
        if (pos_errada) {
            haserror = true;
            if (tremdebits[i][pos_errada - 1]) {
                tremdebits[i][pos_errada - 1] = 0;
            } else {
                tremdebits[i][pos_errada-1] = 1;
            }
        }
        tremcorrigido = {tremdebits[i][2], tremdebits[i][4], tremdebits[i][5], tremdebits[i][6], tremdebits[i][8], tremdebits[i][9], tremdebits[i][10], tremdebits[i][11]};
        resultado.push_back(tremcorrigido);
    }
    for(int i =0; i < resultado.size();i++){
        for(int j = 0; j < resultado[i].size();j++){
            corrigido.push_back(resultado[i][j]);
        }
    }
    if(haserror){
        cout <<"\nErro detectado!!!" << endl;
    }
    return corrigido;
}

/**
 * @brief Método de detecção de erro que adiciona vários bits de paridade no tremdebits.
 * 
 * @param tremdebits 
 * @return vector <int> 
 */
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
/**
 * @brief Método de detecção de erro que verifica se há erro no quadro.
 * 
 * @param tremdebits 
 * @return vector <int> 
 */
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
    for(int i = 0; i < tam-7; i++){
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
    cout << "paridade recebida: " << endl;
    for(int i = 0; i < paridade_recebida.size(); i++){
        cout << paridade_recebida[i];
    }
    return tremdebits;
}

vector <int> CamadaEnlaceTransmissora::ControleDeErroCRC(vector <int> tremdebits) {
    vector <int> aux1, aux2, dividendo;

    for (int i{}; i < tremdebits.size(); i++) {
        dividendo.push_back(tremdebits[i]);
    }

    for (int i{}; i < 33; i++) {
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


vector <int> CamadaEnlaceTransmissora::InsercaoDeBytes(vector <int> quadro) {
    vector <int> aux1;
    size_t tamanhoByte = 8;
    for (int i{}; i < flag.size(); i++) {
        aux1.push_back(flag[i]);
    }
    
    while (quadro.size()) {
        if ((!quadro[0] && !quadro[1] && !quadro[2] && !quadro[3] && quadro[4] && quadro[5] && quadro[6] && quadro[7]) || (!quadro[0] && !quadro[1] && !quadro[2] && !quadro[3] && !quadro[4] && quadro[5] && quadro[6] && !quadro[7])) {
            for (int i{}; i < esc.size(); i++) {
                aux1.push_back(esc[i]);
            }
        }
        for (int i{}; i < 8; i++) {
            aux1.push_back(quadro[i]);
        }
        
        if (quadro.size() >= tamanhoByte) {
            quadro.erase(quadro.begin(), quadro.begin() + tamanhoByte);
        }
        
    }
    for (int i{}; i < flag.size(); i++) {
        aux1.push_back(flag[i]);
    }
    return aux1;
}

vector <int> CamadaEnlaceReceptora::InsercaoDeBytes(vector <int> quadro) {
    vector <int> aux1;
    int isEsc{};
    int isMensagem{};
    size_t tamanhoByte = 8;
    vector<int> error = quadro;

    while (quadro.size()) {
        if (isMensagem) {
            if (isEsc) {
                for (int i{}; i < 8; i++) {
                    aux1.push_back(quadro[i]);
                }
                isEsc = 0;
            } else {
                if (!quadro[0] && !quadro[1] && !quadro[2] && !quadro[3] && quadro[4] && quadro[5] && quadro[6] && quadro[7]) {
                    isMensagem = 0;
                } else if (!quadro[0] && !quadro[1] && !quadro[2] && !quadro[3] && !quadro[4] && quadro[5] && quadro[6] && !quadro[7]) {
                    isEsc = 1;
                } else {
                    for (int i{}; i < 8; i++) {
                        aux1.push_back(quadro[i]);
                    }
                }
            }
        } else {
            if (!quadro[0] && !quadro[1] && !quadro[2] && !quadro[3] && quadro[4] && quadro[5] && quadro[6] && quadro[7]) {
                    isMensagem = 1;
            }
        }
        if (quadro.size() >= tamanhoByte) {
            quadro.erase(quadro.begin(), quadro.begin() + tamanhoByte);
        }
    }
    if(aux1.empty()){
        cout <<"\nErro detectado!!!" << endl;
        cout <<"Flag e Esc inexistentes" << endl;
        return error;
    }
    return aux1;
}