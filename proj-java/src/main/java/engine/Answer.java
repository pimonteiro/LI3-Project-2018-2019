package engine;

import java.time.LocalDateTime;
import java.util.Objects;

public class Answer extends Post {

    private long parent_id;

    public Answer(long id, long owner_id, long score, LocalDateTime creation_date, long parent_id, long n_comments){
        super(id, owner_id, score, creation_date, n_comments);
        this.parent_id = parent_id;
    }

    public Answer(Answer a){
        super(a);
        this.parent_id = a.parent_id;
    }

    public long getParent_id(){
        return this.parent_id;
    }


    @Override
    public String toString(){
        return "Answer{" +
               "parent_id=" + parent_id +
               '}' + super.toString();
    }

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        if(!super.equals(o)) return false;
        Answer answer = (Answer) o;
        return parent_id == answer.parent_id;
    }

    @Override
    public int hashCode(){
        return Objects.hash(super.hashCode(), parent_id);
    }

    public Answer clone(){
        return new Answer(this);
    }

}
