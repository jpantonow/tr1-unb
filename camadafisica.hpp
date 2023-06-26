#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>
using namespace std;
/**
 * @brief Superclasse que representa uma camada genérica.
 * 
 * Tem como atributos públicos e herdáveis no modo public o quadro, o fluxo bruto de bits e um inteiro que representa o tipo de codificação.
 * 
 */
class Camada {
    public:
    vector <int> quadro;
    vector <int> fluxoBrutoDeBits;
    int codificacao;
};

/**
 * @brief Classe que representa a camada física transmissora.
 * 
 * Herda no modo public os atributos da classe Camada.
 * 
 * Representa a camada que irá codificar a mensagem e transmití-la adiante.
 * 
 */
class CamadaFisicaTransmissora: public Camada {
    private:
    /**
     * @brief Constante para representar a codificação binaria.
     * 
     */
    const static int BINARIA = 0;
    /**
     * @brief Constante para representar a codificação manchester.
     * 
     */
    const static int MANCHESTER = 1;
    /**
     * @brief Constante para representar a codificação bipolar.
     * 
     */
    const static int BIPOLAR = 2;
    /**
     * @brief Vetor de inteiros que representa o clock.
     * 
     * Possui os inteiros 0 e 1, a fim de representar os pulsos do clock.
     * 
     */
    vector <int> CLOCK = {0, 1};
    public:
    /**
     * @brief Método que inicia a codificação.
     * 
     * Recebe a mensagem e o tipo de codificação a ser escolhida, para depois transmití-la.
     * 
     * Tem em suas estruturas os métodos para codificar a mensagem, o canal para transmití-la e a camada de aplicacao receptora ao final do processo. 
     * 
     * @param codificacao 
     * @param mensagem 
     */
    void iniciar(int codificacao, string mensagem);
    /**
     * @brief Método que codifica e transmite a mensagem na codificação binaria.
     * 
     * @param quadro 
     * @return vector <int> 
     */
    vector <int> TransmissoraBinaria(vector <int> quadro);
    /**
     * @brief Método que codifica e transmite a mensagem na codificação manchester.
     * 
     * @param quadro 
     * @return vector <int> 
     */
    vector <int> TransmissoraManchester(vector <int> quadro);
    /**
     * @brief Método que codifica e transmite a mensagem na codificação bipolar.
     * 
     * @param quadro 
     * @return vector <int> 
     */
    vector <int> TransmissoraBipolar(vector <int> quadro);
    /**
     * @brief Método que recebe a string mensagem e a transforma em bits.
     * 
     * @param mensagem 
     * @return vector <int> 
     */
    vector <int> ConversorStringBits(string mensagem);
};
/**
 * @brief Classe que representa a camada física receptora.
 * 
 * Herda no modo public os atributos da classe Camada.
 * 
 * Representa a camada que irá receber a mensagem codificada e irá decodificá-la novamente.
 */
class CamadaFisicaReceptora: public Camada {
    public:
    /**
     * @brief Método que converte codificação binária em bits.
     * 
     * @param quadro 
     * @return vector <int> 
     */
    vector <int> ConversorBinarioBits(vector <int> quadro);
    /**
     * @brief Método que converte codificação manchester em bits.
     * 
     * @param quadro 
     * @return vector <int> 
     */
    vector <int> ConversorManchesterBits(vector <int> quadro);
    /**
     * @brief Método que converte codificação bipolar em bits.
     * 
     * @param quadro 
     * @return vector <int> 
     */
    vector <int> ConversorBipolarBits(vector <int> quadro);
    /**
     * @brief Método que converte bits em strings.
     * 
     * @param bitstream 
     * @return string 
     */
    string ConversorBitString(vector<int> bitstream);
    /**
     * @brief Método que recebe a codificação binária e decodifica em uma mensagem.
     * 
     * @param quadro 
     * @return string 
     */
    string ReceptoraBinaria(vector <int> quadro);
    /**
     * @brief Método que recebe a codificação manchester e decodifica em uma mensagem.
     * 
     * @param quadro 
     * @return string 
     */
    string ReceptoraManchester(vector <int> quadro);
    /**
     * @brief Método que recebe a codificação bipolar e decodifica em uma mensagem.
     * 
     * @param quadro 
     * @return string 
     */
    string ReceptoraBipolar(vector <int> quadro);
};
/**
 * @brief Classe que representa a camada de aplicação.
 * 
 * Herda no modo public os atributos da classe Camada.
 * 
 * Recebe a mensagem e a transmite de volta para o usuario.
 * 
 */
class CamadaAplicacao: public Camada {
    private:
    /**
     * @brief Constante para representar a codificação binaria.
     * 
     */
    const static int BINARIA = 0;
    /**
     * @brief Constante para representar a codificação manchester.
     * 
     */
    const static int MANCHESTER = 1;
    /**
     * @brief Constante para representar a codificação bipolar.
     * 
     */
    const static int BIPOLAR = 2;
    public:
    /**
     * @brief String que representa a mensagem recebida.
     * 
     */
    string mensagem;
    /**
     * @brief Método que inicia o processo e o finaliza, do transmissor ao receptor.
     * 
     */
    void Transmissora();
    /**
     * @brief Método que recebe o fluxo bruto de bits, decodifica e imprime a mensagem recebida.
     * 
     * @param fluxoBrutoDeBits 
     * @param codificacao 
     * @return vector <int> 
     */
    vector <int> Receptora(vector <int> fluxoBrutoDeBits, int codificacao);
    /**
     * @brief Método demonstrativo para representar como seria a mensagem codificada.
     * 
     * @param fluxoBrutoDeBits 
     * @param codificacao 
     */
    void MensagemCodificada(vector <int> fluxoBrutoDeBits, int codificacao);
    /**
     * @brief Método que imprime a mensagem recebida ao usuário.
     * 
     */
    void MensagemRecebida(string);
};
/**
 * @brief Classe que representa o meio de comunicação em que a mensagem codificada será transmitida.
 * 
 */
class MeioDeComunicacao{
    private:
    public:
    /**
     * @brief Transmite os bits de um ponto a outro, retornando-os.
     * 
     * @param fluxoBrutoDeBits 
     * @return vector <int> 
     */
    vector <int> Comunicacao(vector <int> fluxoBrutoDeBits);
};

