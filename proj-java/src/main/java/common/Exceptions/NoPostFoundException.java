package common.Exceptions;

/**
 * @brief Método que verifica se um ID existe entre os Posts
 * @return Mensagem de erro\
 */

public class NoPostFoundException extends Exception {

    public NoPostFoundException(){
        super("No Post found with given ID");
    }
}
