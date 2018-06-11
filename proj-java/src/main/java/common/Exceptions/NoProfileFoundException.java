package common.Exceptions;

/**
 * @brief Método que verifica se um ID existe entre os perfis
 */

public class NoProfileFoundException extends Exception {

    public NoProfileFoundException(){
        super("No profile with given ID");
    }
}
