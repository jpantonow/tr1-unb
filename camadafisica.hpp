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
    vector <int> ConversorBinarioBits(vector <int> quadro);
    vector <int> ConversorManchesterBits(vector <int> quadro);
    vector <int> ConversorBipolarBits(vector <int> quadro);
    string ConversorBitString(vector<int> bitstream);
    string ReceptoraBinaria(vector <int> quadro);
    string ReceptoraManchester(vector <int> quadro);
    string ReceptoraBipolar(vector <int> quadro);
};
class CamadaAplicacao: public Camada {
    private:
    const static int BINARIA = 0;
    const static int MANCHESTER = 1;
    const static int BIPOLAR = 2;
    public:
    string mensagem;
    void Transmissora();
    vector <int> Receptora(vector <int> fluxoBrutoDeBits, int codificacao);
    void MensagemCodificada(vector <int> fluxoBrutoDeBits, int codificacao);
    void MensagemRecebida(string);
};

class MeioDeComunicacao{
    private:
    public:
    vector <int> Comunicacao(vector <int> fluxoBrutoDeBits);
};

