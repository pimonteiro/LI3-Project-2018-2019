package common;

public class NoProfileFoundException extends Exception {

    public NoProfileFoundException(){
        super("No profile with given ID");
    }
}
