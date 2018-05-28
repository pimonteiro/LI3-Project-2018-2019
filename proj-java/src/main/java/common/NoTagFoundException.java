package common;

public class NoTagFoundException extends Exception {

    public NoTagFoundException(){
        super("No Tag found with given string");
    }
}
