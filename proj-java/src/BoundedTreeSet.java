import javax.swing.*;
import java.util.Comparator;
import java.util.TreeSet;

public class BoundedTreeSet<E> extends TreeSet<E> {
    private int limit;

    public BoundedTreeSet(int size){
        super();
        this.limit = limit;
    }

    public BoundedTreeSet(int size, Comparator c){
        super(c);
        this.limit = limit;
    }

    @Override
    public boolean add(E e){
        super.add(e);
        if(this.size() > this.limit){
            this.remove(this.last());
        }
        return true;
    }
}
