#include "camadafisica.hpp"
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

    const static int CONTAGEM = 0;
    const static int INSERCAO = 1;

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
    void Receptora(vector <int> fluxoBrutoDeBits, int codificacao);
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
    void MensagemEnquadrada(vector <int> fluxoBrutoDeBits, int codificacao);
    void MensagemRecebida(string);
    /**
     * @brief Método que recebe a string mensagem e a transforma em bits.
     * 
     * @param mensagem 
     * @return vector <int> 
     */
    vector <int> ConversorStringBits(string mensagem);
};