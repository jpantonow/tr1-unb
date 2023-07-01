#include <math.h>
#include "./camadafisica.hpp"
#include <bitset>
using namespace std;

/**
 * @brief Método que transforma string em bits.
 * 
 * Simula um conversor de mensagem para binário.
 * 
 * @param mensagem 
 * @return vector <int> 
 */
vector <int> CamadaFisicaTransmissora::ConversorStringBits(string mensagem) {
    vector <int> mensagemBitStream;

    for (int i {}; i < mensagem.size(); ++i) {
        bitset<8> bits(mensagem[i]);
        string bitsString =  bits.to_string();
        for (int j {}; j < bitsString.size(); ++j) {
            int bit = static_cast<int>(bitsString[j]);
            mensagemBitStream.push_back(bit-48);
        }
    }
    return mensagemBitStream;
}


/**
 * @brief Método que converte bits em string.
 * 
 * Utiliza conceitos relativos à tabela ASCII para a conversão.
 * 
 * Método que simula a decodificação da mensagem.
 * 
 * Síntese do método: converter o byte para um número decimal e descobrir correspondente de cada letra em char.
 * 
 * Final do método: concatenação de caracteres
 * 
 * @param bitstream 
 * @return string 
 */
string CamadaFisicaReceptora::ConversorBitString(vector <int> bitstream) {
    string mensagem;
    vector <int> resultado;
    for(int i = 0; i < bitstream.size(); i++) {
        if (i % 8 == 0) { // Indica se formou um byte
            int soma = 0; //Acumulação da soma
            for (int j = 0; j < resultado.size(); j++) {
                int a = int(pow(2, j));
                soma += int(resultado[7-j]*a); //Soma que acumula o número decimal correspondente
            }
            char caractere;
            caractere = char(soma); //conversão para caractere
            mensagem += caractere;
            resultado.clear();
            resultado.push_back(bitstream[i]);
            soma = 0;
        } else if(i == bitstream.size() -1) { //se for o último bit do conjunto
            resultado.push_back(bitstream[i]);
            int soma = 0;
            for (int j = 0; j < resultado.size(); j++) {
                int a = int(pow(2, j));
                soma += int(resultado[7-j] *a); //Soma que acumula o número decimal correspondente
            }
            char caractere;
            caractere = char(soma);
            mensagem += caractere;
            resultado.clear();
            resultado.push_back(bitstream[i]);
            soma = 0;
        } else {
        resultado.push_back(bitstream[i]);
        }
    }
    return mensagem;
}

/**
 * @brief Método que começa a simulação.
 * 
 * O usuário insere uma mensagem e escolhe a codificação que ela será transmitida.
 * 
 * Após a inserção das informações, inicia-se a transmissão via camada física transmissora.
 * 
 */
void CamadaAplicacao::Transmissora() {
    cout << "Escolha uma mensagem a ser codificada: " << endl;
    getline(cin, mensagem);
    cout << "Escolha um tipo de codificacao a ser utilizada: " << endl;
    cout << "0 - Binaria" << endl;
    cout << "1 - Manchester" << endl;
    cout << "2 - Bipolar" << endl;
    cout << "Sua escolha: ";
    cin >> codificacao;
    CamadaFisicaTransmissora camadaFisicaTransmissora;
    camadaFisicaTransmissora.iniciar(codificacao, mensagem);
}

/**
 * @brief Método que simula a camada física transmissora.
 * 
 * Recebe a mensagem e a codifica na codificação escolhida.
 * 
 * Após codificada a mensagem, repassa o resultado para a camada física tranmissora, que retornará o fluxo bruto de bits.
 * 
 * Ao final do método, repassa o fluxo bruto de bits pelo meio de comunicação, e, após comunicado, transmite à camada de aplicação receptora.
 * 
 * @param codificacao 
 * @param mensagem 
 */
void CamadaFisicaTransmissora::iniciar(int codificacao, string mensagem) {
    CamadaAplicacao camadaAplicacao;
    MeioDeComunicacao meioDeComunicacao;
    switch (codificacao) {
        case BINARIA:
            //converte as strings em bits
            quadro = ConversorStringBits(mensagem);
            //repassa o resultado para a camada física transmissora binária
            fluxoBrutoDeBits = TransmissoraBinaria(quadro);
            break;
        case MANCHESTER:
            //converte as strings em bits
            quadro = ConversorStringBits(mensagem);
            //repassa o resultado para a camada física transmissora manchester
            fluxoBrutoDeBits = TransmissoraManchester(quadro);
            break;
        case BIPOLAR:
            //converte as strings em bits
            quadro = ConversorStringBits(mensagem);
             //repassa o resultado para a camada física transmissora bipolar
            fluxoBrutoDeBits = TransmissoraBipolar(quadro);
            break;
}
//Passa o fluxo bruto de bits para o meio de comunicação
vector <int> fluxoComunicado = meioDeComunicacao.Comunicacao(fluxoBrutoDeBits);
//Passa o fluxo ja comunicado junto da codificação escolhida
    camadaAplicacao.Receptora(fluxoComunicado, codificacao);
}
/**
 * @brief Camada Física Transmissora binária recebe os bits e os repassa.
 * 
 * @param quadro 
 * @return vector <int> 
 */
vector <int> CamadaFisicaTransmissora::TransmissoraBinaria(vector <int> quadro) {
    return quadro;
}

/**
 * @brief Camada Física Transmissora Manchester recebe os bits e os codifica em Manchester, repassando-os ao final do método.
 * 
 * @param quadro 
 * @return vector <int> 
 */
vector <int> CamadaFisicaTransmissora::TransmissoraManchester(vector <int> quadro) {
    vector <int> tremDeBits;
    for (int i = 0; i < quadro.size(); i++) { 
        tremDeBits.push_back(CLOCK[0] ^ quadro[i]); //realização de XOR entre o bit 0 do clock e o bit do quadro
        tremDeBits.push_back(CLOCK[1] ^ quadro[i]); //realização de XOR entre o bit 1 do clock e o bit do quadro
    }

    return tremDeBits;
}

/**
 * @brief Camada Física Transmissora Bipolar recebe os bits e os codifica em Bipolar, repassando-os ao final do método.
 * 
 * @param quadro 
 * @return vector <int> 
 */
vector <int> CamadaFisicaTransmissora::TransmissoraBipolar(vector <int> quadro) {
    vector <int> tremDeBits;
    int sinal {};
    for (int i = 0; i < quadro.size(); ++i) {
        if (quadro[i]) {
            if (sinal) {
                tremDeBits.push_back(11);
                sinal = 0;
            } else {
                tremDeBits.push_back(10);
                sinal = 1;
            }
        } else {
            tremDeBits.push_back(0);
    }
}
return tremDeBits;
}
/**
 * @brief Método que converte uma mensagem na codificação manchester para bits.
 * 
 * @param quadro 
 * @return vector <int> 
 */
vector <int> CamadaFisicaReceptora::ConversorManchesterBits(vector <int> quadro) {
    vector <int> bitstream;

    for (int i = 0; i < quadro.size()/2; ++i) {
        if (quadro[i*2]) { 
            bitstream.push_back(1);
        } else {
            bitstream.push_back(0);
        }
    }
    return bitstream;
}

/**
 * @brief Método que decodifica a mensagem codificada em binário para bits.
 * 
 * @param quadro 
 * @return vector <int> 
 */
vector <int> CamadaFisicaReceptora::ConversorBinarioBits(vector <int> quadro) {
    vector <int> bitstream;
    for (int i = 0; i < quadro.size(); ++i) {
        if (quadro[i]) {
            bitstream.push_back(1);
        } else {
            bitstream.push_back(0);
        }
    }

    return bitstream;
}
/**
 * @brief Método que decodifica a mensagem codificada em bipolar para bits.
 * 
 * @param quadro 
 * @return vector <int> 
 */
vector <int> CamadaFisicaReceptora::ConversorBipolarBits(vector <int> quadro) {
    vector <int> bitstream;

    for (int i = 0; i < quadro.size(); ++i) {
        if (quadro[i]) {
            bitstream.push_back(1);
        } else {
            bitstream.push_back(0);
        }
    }

    return bitstream;
}

/**
 * @brief Método que recebe a mensagem codificada em binário e a decodifica, retornando a mensagem.
 * 
 * @param quadro 
 * @return string 
 */
string CamadaFisicaReceptora::ReceptoraBinaria(vector <int> quadro) {
    vector <int> bitstream = ConversorBinarioBits(quadro);
    string mensagem = ConversorBitString(bitstream);
    return mensagem;
}
/**
 * @brief Método que recebe a mensagem codificada em manchester e a decodifica, retornando a mensagem.
 * 
 * @param quadro 
 * @return string 
 */
string CamadaFisicaReceptora::ReceptoraManchester(vector <int> quadro) {
    vector <int> bitstream = ConversorManchesterBits(quadro);
    string mensagem = ConversorBitString(bitstream);
    return mensagem;
}
/**
 * @brief Método que recebe a mensagem codificada em bipolar e a decodifica, retornando a mensagem.
 * 
 * @param tremDeBits 
 * @return string 
 */
string CamadaFisicaReceptora::ReceptoraBipolar(vector <int> tremDeBits) {
    vector <int> bitstream = ConversorBipolarBits(tremDeBits);
    string mensagem = ConversorBitString(bitstream);
    return mensagem;
}
/**
 * @brief Método que simula a camada de aplicação receptora.
 * 
 * De acordo com a codificação escolhida, realiza os mecanismos pra receber a mensagem e convertê-la em string.
 * 
 * Ao final do processo, imprime a mensagem decodificada.
 * 
 * @param fluxoBrutoDeBits 
 * @param codificacao 
 */
void CamadaAplicacao::Receptora(vector <int> fluxoBrutoDeBits, int codificacao) {
    MensagemCodificada(fluxoBrutoDeBits, codificacao);
    CamadaFisicaReceptora receptora;
    string mensagem;

    switch (codificacao) {
        case BINARIA:
        {   mensagem = receptora.ReceptoraBinaria(fluxoBrutoDeBits);
            MensagemRecebida(mensagem);
            break;
        }
        case MANCHESTER:
        {   mensagem = receptora.ReceptoraManchester(fluxoBrutoDeBits);
            MensagemRecebida(mensagem);
            break;
        }
        case BIPOLAR:
        {
            mensagem = receptora.ReceptoraBipolar(fluxoBrutoDeBits);
            MensagemRecebida(mensagem);
            break;
        }
    }
}

/**
 * @brief Método demonstrativo para ilustrar como seria a mensagem codificada.
 * 
 * De acordo com o respectivo tipo de codificação, imprime a mensagem codificada. 
 * 
 * @param fluxoBrutoDeBits 
 * @param codificacao 
 */
void CamadaAplicacao::MensagemCodificada(vector <int> fluxoBrutoDeBits, int codificacao) {
    cout << "A mensagem codificada pode ser representada por: " << endl;
    for (int i=0; i < fluxoBrutoDeBits.size(); i++) {
        if (codificacao == 2) {
            if ((i%8 == 0) & (fluxoBrutoDeBits[i] == 0)) {
            cout <<"\n0" << fluxoBrutoDeBits[i];
        } else if ((i%8 == 0) & (fluxoBrutoDeBits[i] != 0)) {
            cout <<"\n" << fluxoBrutoDeBits[i];
        } else {
            if (fluxoBrutoDeBits[i] == 11 || fluxoBrutoDeBits[i] == 10) {
                cout << " " << fluxoBrutoDeBits[i];
            } else {
                cout << " 0" << fluxoBrutoDeBits[i];
            }
        }
        } else {
        if (i%8 == 0) {
            cout <<"\n" << fluxoBrutoDeBits[i];
        } else {
        if (fluxoBrutoDeBits[i] == 11 || fluxoBrutoDeBits[i] == 10) {
            cout << " " << fluxoBrutoDeBits[i];
        } else {
            cout << "  " << fluxoBrutoDeBits[i];
        }
        }
    }
    }
}
/**
 * @brief Método para imprimir uma mensagem.
 * 
 * @param mensagem 
 */
void CamadaAplicacao::MensagemRecebida(string mensagem) {
    cout << "\n";
    cout << "\nA mensagem recebida foi: " << mensagem << endl;
}

/**
 * @brief Método para simular um meio de comunicação.
 * 
 * Transporta um fluxo bruto de bits entre dois pontos.
 * 
 * @param fluxoBrutoDeBits 
 * @return vector <int> 
 */
vector <int> MeioDeComunicacao::Comunicacao(vector <int> fluxoBrutoDeBits) {
    vector <int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
    for (int i = 0; i < fluxoBrutoDeBitsPontoA.size(); i++) {
        fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA[i]);
    }
    return fluxoBrutoDeBitsPontoB;
}
