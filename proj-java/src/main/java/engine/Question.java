package engine;

import java.time.LocalDateTime;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * @brief Question que extende de Post.
 * Possui um Map com as respostas desta Question, titulo, lista de tags e número de respostas.
 */

public class Question extends Post {

    private Map<Long,Answer> answers;
    private String title;
    private List<String> tags;
    private long n_answers;

    private List<String> tagstoList(String tags){
        String regexString = Pattern.quote("<") + "(.*?)" + Pattern.quote(">");
        Pattern pattern = Pattern.compile(regexString);
        Matcher matcher = pattern.matcher(tags);
        List<String> tmp = new ArrayList<>();
        while(matcher.find()){
            String textInBetween = matcher.group(1); // Since (.*?) is capturing group 1
            tmp.add(textInBetween);
        }

        return tmp;
    }

 /** @brief Construtor parametrizado da Questão
  *  @param id,owner_id,score,creation_date,comments,title Titulo de uma Questão, n_answers Número de respostas,
  *  @param tags Tags, answersl HashMap com as respostas de uma dada Questão
 */

    public Question(long id, long owner_id, long score, LocalDateTime creation_date, String title, long n_answers,
                    long comments, String tags, Map<Long,Answer> answersl){

        super(id, owner_id, score, creation_date, comments);
        this.title = title;
        this.n_answers = n_answers;
        this.tags = new ArrayList<>(tagstoList(tags));
        this.answers = new HashMap<>();

        for(Map.Entry<Long,Answer> a : answersl.entrySet()){
            this.answers.put(a.getKey(), a.getValue().clone());
        }
    }

/**
 * @brief Construtor por cópia de uma questão
 */

    public Question(Question q){
        super(q);
        this.title = q.title;
        this.n_answers = q.n_answers;
        this.tags = q.tags;
        this.answers = new HashMap<>();

        for(Map.Entry<Long,Answer> a : q.answers.entrySet()){
            this.answers.put(a.getKey(), a.getValue().clone());
        }
    }

/**
 *@brief Construtor parametrizado de uma Questão
 */

    public Question(long id, long owner_id, long score, LocalDateTime creation_date, long n_comments, String title,
                    long n_answers, String tags){
        super(id, owner_id, score, creation_date, n_comments);
        this.title = title;
        this.n_answers = n_answers;
        this.tags = tags == null ? new ArrayList<>() : new ArrayList<>(tagstoList(tags));
        this.answers = new HashMap<>();

    }

/**
 * @brief Getters relativos às questões
 */

    public Map<Long,Answer> getAnswers(){
        return answers;
    }

    public String getTitle(){
        return title;
    }

    public List<String> getTags(){
        return tags;
    }

    public long getN_answers(){
        return n_answers;
    }

/**
 * @brief Setter da HashMap de answers
 */
    public void setAnswers(Map<Long,Answer> ans){
        this.answers = new HashMap<>();
        ans.forEach((k,v) -> this.answers.put(k, v.clone()));
    }

/**
 * @brief Método equals de uma Questão
 */

    @Override
    public boolean equals(Object o){
        if(this == o) return true;
        if(o == null || getClass() != o.getClass()) return false;
        if(!super.equals(o)) return false;
        Question question = (Question) o;
        return n_answers == question.n_answers &&
               Objects.equals(answers, question.answers) &&
               Objects.equals(title, question.title) &&
               Objects.equals(tags, question.tags);
    }
/**
 * @brief Método HashCode para Questão
 */

    @Override
    public int hashCode(){

        return Objects.hash(super.hashCode(), answers, title, tags, n_answers);
    }

    /**
     * @brief Método toString de uma Questão
     */

    @Override
    public java.lang.String toString(){
        return "Question{" +
               "answers=" + answers +
               ", title=" + title +
               ", tags=" + tags +
               ", n_answers=" + n_answers +
               '}' + super.toString();
    }

    /**
     * @brief Método clone de uma Questão
     */

    public Question clone(){
        return new Question(this);
    }

    /**
     * @brief Adiciona uma resposta á lista de respostas.
     * @param a
     */

    public void addAnswer(Answer a){
        this.answers.put(a.getId(), a);
        ++(this.n_answers);
    }

}
