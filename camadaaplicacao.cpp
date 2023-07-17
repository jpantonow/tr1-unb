#include "camadaaplicacao.hpp"
#include "camadaenlace.cpp"
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
    cout << "1 - Insercao de Bytes" << endl;
    cout << "Sua escolha: " << endl;
    cin >> enquadramento;
    cout << "Escolha um tipo de erro: " << endl;
    cout << "0: Bit de paridade par" << endl;
    cout << "1: CRC" << endl;
    cout << "2: Hamming" << endl;
    cin >> erro;
    cout << "Escolha uma porcentagem de erro(50%, 75%, 100%) :" << endl;
    cin >> porcentagem;
    cout << "Escolha um tipo de codificacao a ser utilizada: " << endl;
    cout << "0 - Binaria" << endl;
    cout << "1 - Manchester" << endl;
    cout << "2 - Bipolar" << endl;
    cout << "Sua escolha: ";
    cin >> codificacao;
    CamadaFisicaTransmissora camadaFisicaTransmissora;
    vector <int> binario = ConversorStringBits(mensagem);
    CamadaEnlaceTransmissora camadaEnlaceTransmissora;
    vector <int> enquadrado = camadaEnlaceTransmissora.iniciar(erro,enquadramento,binario);
    //mudar o binario da camada fisica transmissora pra receber o enquadrado
    camadaFisicaTransmissora.iniciar(codificacao, enquadrado, porcentagem, erro, enquadramento);
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
void CamadaAplicacao::Receptora(vector <int> fluxoBrutoDeBits, int codificacao, int erro, int enquadramento) {
    //MensagemCodificada(fluxoBrutoDeBits, codificacao);
    // CamadaEnlaceTransmissora camadaEnlace;
    // vector <int> enlace;
    // enlace = camadaEnlace.ContagemDeCaracteres(fluxoBrutoDeBits);
    MensagemCodificada(fluxoBrutoDeBits, codificacao);
    CamadaFisicaReceptora receptora;
    string mensagem;
    //CamadaEnlaceReceptora receptoraenlace;
    //vector <int> desenquadrado;
    //desenquadrado = receptoraenlace.iniciar(enquadramento, erro, fluxoBrutoDeBits);
    switch (codificacao) {
        case BINARIA:
        {   mensagem = receptora.ReceptoraBinaria(fluxoBrutoDeBits, enquadramento, erro);
            MensagemRecebida(mensagem);
            break;
        }
        case MANCHESTER:
        {   mensagem = receptora.ReceptoraManchester(fluxoBrutoDeBits, enquadramento, erro);
            MensagemRecebida(mensagem);
            break;
        }
        case BIPOLAR:
        {
            mensagem = receptora.ReceptoraBipolar(fluxoBrutoDeBits, enquadramento, erro);
            MensagemRecebida(mensagem);
            break;
        }
    }
    Retransmitir();
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
    cout << "\nA mensagem codificada pode ser representada por: " << endl;
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

void CamadaAplicacao::Retransmitir(){
    string confirmacao;
    cout << "\nDeseja retransmitir a mensagem? " << endl;
    getline(cin,confirmacao);
    if(confirmacao=="sim" or confirmacao=="SIM"){
        Transmissora();
    }

}