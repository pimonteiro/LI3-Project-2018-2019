import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Objects;

public class Question extends Post {
    private LocalDate creation_date;
    private ArrayList<Long> id_answers;
    private String title;
    private String tags; //TODO Maybe we can change with java
    private long id;
    private long owner_id;
    private long n_answers;
    private long comments;
    private long score;

    public Question(LocalDate creation_date, ArrayList<Long> id_answers, String title_question, String tags, long id_question, long owner_id_question, long n_answers, long comments, long score) {
        super(1); //1 - Questao
        this.creation_date = creation_date;
        this.id_answers = id_answers;
        this.title = title_question;
        this.tags = tags;
        this.id = id_question;
        this.owner_id = owner_id_question;
        this.n_answers = n_answers;
        this.comments = comments;
        this.score = score;
    }

    public Question(Question q){
        super(q);
        this.creation_date = q.getCreation_date();
        this.id_answers = q.getId_answers();
        this.title = q.getTitle();
        this.tags = q.getTags();
        this.id = q.getId();
        this.owner_id = q.getOwner_id();
        this.n_answers = q.getN_answers();
        this.comments = q.getComments();
        this.score = q.getScore();
    }

    public Question(){
        super();
        this.creation_date = LocalDate.now();
        this.id_answers = new ArrayList<>();
        this.title = "";
        this.tags = "";
        this.id = -1;
        this.owner_id = -1;
        this.n_answers = -1;
        this.comments = -1;
        this.score = -1;
    }

    public LocalDate getCreation_date() {
        return this.creation_date;
    }

    public ArrayList<Long> getId_answers() {
        return this.id_answers;
    }

    public String getTitle() {
        return this.title;
    }

    public String getTags() {
        return this.tags;
    }

    public long getId() {
        return this.id;
    }

    public long getOwner_id() {
        return this.owner_id;
    }

    public long getN_answers() {
        return this.n_answers;
    }

    public long getComments() {
        return this.comments;
    }

    public long getScore() {
        return this.score;
    }

    public void setCreation_date(LocalDate creation_date) {
        this.creation_date = creation_date;
    }

    public void setId_answers(ArrayList<Long> id_answers) {
        this.id_answers = id_answers;
    }

    public void setTitle(String title_question) {
        this.title = title_question;
    }

    public void setTags(String tags) {
        this.tags = tags;
    }

    public void setId(long id_question) {
        this.id = id_question;
    }

    public void setOwner_id(long owner_id_question) {
        this.owner_id = owner_id_question;
    }

    public void setN_answers(long n_answers) {
        this.n_answers = n_answers;
    }

    public void setComments(long comments) {
        this.comments = comments;
    }

    public void setScore(long score) {
        this.score = score;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || o.getClass() != this.getClass()) return false;
        if (!super.equals(o)) return false;

        Question q = (Question) o;
        return this.id == q.getId() &&
                this.owner_id == q.getOwner_id() &&
                this.n_answers == q.getN_answers() &&
                this.comments == q.getComments() &&
                this.score == q.getScore() &&
                this.creation_date.equals(q.getCreation_date()) &&
                this.id_answers.equals(q.getId_answers()) &&
                this.title.equals(q.getTitle()) &&
                this.tags.equals(q.getTags());
    }

    public Question clone(){
        return new Question(this);
    }

    public String toString(){
        return "ID: " + this.id + "Onwer ID: " + this.owner_id +
                "N_answers: " + this.n_answers + "Comments: " + this.comments +
                "Score: " + this.score + "Creation Date :" + this.creation_date +
                "Title: " + this.title +
                "ID_answers: " + this.id_answers.toString() + "Tags: " + this.tags;
    }

}
