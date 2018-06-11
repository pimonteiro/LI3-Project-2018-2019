package common.Exceptions;

public class NoProfileFoundException extends Exception {

    public NoProfileFoundException(){
        super("No profile with given ID");
    }
}