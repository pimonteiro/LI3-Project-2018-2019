package engine;

import java.time.LocalDateTime;
import java.util.Objects;

/**
 * @brief Post, de onde extendem as Question e Answer.
 * Esta possui um ID, data de criação, ID do user a que pertence, score e número de comentários.
 */
public abstract class Post implements Comparable<Post> {

    private long id;
    private LocalDateTime creation_date;
    private long owner_id;
    private long score;
    private long n_comments;

    /**
     * @param ID id de um Post,owner_id ID do Post a que pertence,score,número de comentários e data de criação
     * @brief Construtor parametrizado do Post
     */

    public Post(long id, long owner_id, long score, LocalDateTime creation_date, long n_comments){
        this.id = id;
        this.owner_id = owner_id;
        this.score = score;
        this.creation_date = creation_date;
        this.n_comments = n_comments;
    }

    /**
     * @brief Construtor por cópia do Post
     */

    public Post(Post p){
        this.id = p.id;
        this.owner_id = p.owner_id;
        this.score = p.score;
        this.creation_date = p.creation_date;
        this.n_comments = p.n_comments;
    }

    /**
     * @brief Métodos que devolvem getters de um Post para aceder às suas variáveis de instância
     */

    public long getId(){
        return this.id;
    }

    public long getOwner_id(){
        return this.owner_id;
    }

    public long getScore(){
        return this.score;
    }

    public long getN_comments(){
        return this.n_comments;
    }

    public LocalDateTime getCreation_date(){
        return this.creation_date;
    }

    /**
     * @brief Método toString de um Post
     */

    @Override
    public String toString(){
        return "Post{" +
               "id=" + id +
               ", creation_date=" + creation_date +
               ", owner_id=" + owner_id +
               ", score=" + score +
               ", n_comments=" + n_comments +
               '}';
    }

    /**
     * @brief Método boolean equals de um Post
     */

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        Post post = (Post) o;
        return id == post.id &&
               owner_id == post.owner_id &&
               score == post.score &&
               n_comments == post.n_comments &&
               Objects.equals(creation_date, post.creation_date);
    }

    @Override
    public int hashCode(){
        return Objects.hash(id, creation_date, owner_id, score, n_comments);
    }

    /**
     * @brief Método clone de um Post
     */
    @Override
    public abstract Post clone();

    /**
     * @param p Post
     * @return True se for igual, False caso contrário
     *
     * @brief Compara a data de criação de um Post com a passada como parametro
     */

    public int compareTo(Post p){
        return this.creation_date.compareTo(p.getCreation_date());
    }

    /**
     * @param begin Data de inicio.
     * @param end   Data do fim
     * @return True se estiver no intervalo, False em contrário.
     *
     * @brief Verifica se este post está entre duas datas.
     */
    public boolean isBetweenDates(LocalDateTime begin, LocalDateTime end){
        return this.creation_date.isBefore(end) && this.creation_date.isAfter(begin);
    }


}

