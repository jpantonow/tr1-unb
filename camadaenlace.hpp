#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include "camadafisica.hpp"
using namespace std;

/**
 * @brief Classe que representa a camada de enlace transmissora.
 * 
 * Herda no modo public os atributos da classe Camada.
 * 
 * Representa a camada que irá codificar a mensagem e transmití-la adiante.
 * 
 */
class CamadaEnlaceTransmissora: public Camada {
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
 * @brief Classe que representa a camada de enlace receptora.
 * 
 * Herda no modo public os atributos da classe Camada.
 * 
 * Representa a camada que irá receber a mensagem codificada e irá decodificá-la novamente.
 */
class CamadaEnlaceReceptora: public Camada {
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

