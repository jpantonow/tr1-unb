#include "camadaaplicacao.hpp"

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
    cout << "Escolha um tipo de enquadramento a ser utilizado:" << endl;
    cout << "0 - Contagem de Caracteres" << endl;
    cout << "1 - Inserção de Bytes" << endl;
    cout << "Sua escolha: " << endl;
    cin >> enquadramento;
    cout << "Escolha um tipo de erro: " << endl;
    cout << "0: Bit de paridade par" << endl;
    cout << "1: CRC" << endl;
    cout << "2: Hamming" << endl;
    cin >> erro;   
    cout << "Escolha um tipo de codificacao a ser utilizada: " << endl;
    cout << "0 - Binaria" << endl;
    cout << "1 - Manchester" << endl;
    cout << "2 - Bipolar" << endl;
    cout << "Sua escolha: ";
    cin >> codificacao;
    CamadaFisicaTransmissora camadaFisicaTransmissora;
    vector <int> binario = ConversorStringBits(mensagem);
    camadaFisicaTransmissora.iniciar(codificacao, binario);
}
/**
 * @brief Método que transforma string em bits.
 * 
 * Simula um conversor de mensagem para binário.
 * 
 * @param mensagem 
 * @return vector <int> 
 */
vector <int> CamadaAplicacao::ConversorStringBits(string mensagem) {
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
