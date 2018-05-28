package common;

public class NoPostFoundException extends Exception {

    public NoPostFoundException(){
        super("No Post found with given ID");
    }
}