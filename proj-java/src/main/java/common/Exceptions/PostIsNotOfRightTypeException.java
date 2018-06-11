package common.Exceptions;

/**
 * @brief Função que verifica se uma query exige um tipo de post mas recebe outro
 * @param msg Mensagem
 * @return mensagem de erro
 */

public class PostIsNotOfRightTypeException extends Exception {

    public PostIsNotOfRightTypeException(String msg){
        super(msg);
    }
}
