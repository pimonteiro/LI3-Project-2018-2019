package common.Exceptions;

/**
 * @brief Método que verifica caso um ID não exista entre as tags\
 */

public class NoTagFoundException extends Exception {

    public NoTagFoundException(){
        super("No Tag found with given string");
    }
}
