package common;

import javax.swing.*;
import java.util.Comparator;
import java.util.TreeSet;

public class BoundedTreeSet<E> extends TreeSet<E> {
    private int limit;

    public BoundedTreeSet(int size){
        super();
        this.limit = size;
    }

    public BoundedTreeSet(int size, Comparator c){
        super(c);
        this.limit = size;
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
