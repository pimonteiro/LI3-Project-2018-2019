package engine;

import java.time.LocalDateTime;
import java.util.Objects;

public class Answer extends Post {

    private long parent_id;
    private long n_comments;

    public Answer(long id, long owner_id, long score, LocalDateTime creation_date, long parent_id, long n_comments){
        super(id, owner_id, score, creation_date);
        this.parent_id = parent_id;
        this.n_comments = n_comments;
    }

    public Answer(Answer a){
        super(a);
        this.parent_id = a.parent_id;
        this.n_comments = a.n_comments;
    }

    public long getParent_id(){
        return this.parent_id;
    }

    public long getN_comments(){
        return this.n_comments;
    }

    @Override
    public String toString(){
        return "Answer{" +
               "parent_id=" + parent_id +
               ", n_comments=" + n_comments +
               '}' + super.toString();
    }

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        if(!super.equals(o)) return false;
        Answer answer = (Answer) o;
        return parent_id == answer.parent_id &&
               n_comments == answer.n_comments;
    }

    @Override
    public int hashCode(){
        return Objects.hash(super.hashCode(), parent_id, n_comments);
    }

    public Answer clone(){
        return new Answer(this);
    }

}
