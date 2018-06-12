package engine;

import java.time.LocalDateTime;
import java.util.Objects;

/**
 * @brief Anwser extendida de um Post.
 * Possui apenas mais o ID da questao a que pertence.
 */

public class Answer extends Post {

    private long parent_id;


    /**
     * @param id,owner_id,score,creation_date,n_comments,parent_id ID da questão a que pertence
     * @brief Construtor parametrizado da Resposta
     */

    public Answer(long id, long owner_id, long score, LocalDateTime creation_date, long parent_id, long n_comments){
        super(id, owner_id, score, creation_date, n_comments);
        this.parent_id = parent_id;
    }

    /**
     * @brief Construtor por cópia de uma resposta
     */

    public Answer(Answer a){
        super(a);
        this.parent_id = a.parent_id;
    }

    /**
     * @brief Getters relativos às respostas
     */

    public long getParent_id(){
        return this.parent_id;
    }


    /**
     * @brief Método equals de uma Resposta
     */

    @Override
    public String toString(){
        return "Answer{" +
               "parent_id=" + parent_id +
               '}' + super.toString();
    }

    /**
     * @brief Método equals de uma Resposta
     */

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        if(!super.equals(o)) return false;
        Answer answer = (Answer) o;
        return parent_id == answer.parent_id;
    }

    /**
     * @brief Método HashCode
     */

    @Override
    public int hashCode(){
        return Objects.hash(super.hashCode(), parent_id);
    }

    /**
     * @brief Método clone de uma Resposta
     */

    public Answer clone(){
        return new Answer(this);
    }

}
