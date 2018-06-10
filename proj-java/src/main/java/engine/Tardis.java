package engine;


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Tardis {

    // TODO First draft

    private Map<Long,Map<Long,List<Question>>> questions;
    private Map<Long,Map<Long,List<Answer>>> answer;

    public Tardis(){
        this.questions = new HashMap<>();
        this.answer = new HashMap<>();
    }

    public void insert(Object o){
        if(!(o instanceof Post)) return;
        Post tmp = (Post) o;

        long index_year = tmp.getCreation_date().getYear() - 2008;
        long index_mes = (tmp.getCreation_date().getDayOfMonth() - 1) + (31 * (tmp.getCreation_date().getMonthValue()
                                                                               - 1));

        if(tmp instanceof Question){

            Map<Long,List<Question>> anos = this.questions.get(index_year);
            if(anos == null){
                this.questions.put(index_year, new HashMap<>());
                anos = this.questions.get(index_year);
            }

            List<Question> quests = anos.get(index_mes);
            if(quests == null){
                anos.put(index_mes, new ArrayList<>());
                quests = anos.get(index_mes);
            }

            Question q = (Question) tmp;
            quests.add(q);
        }

        if(tmp instanceof Answer){

            Map<Long,List<Answer>> anos = this.answer.get(index_year);
            if(anos == null){
                this.answer.put(index_year, new HashMap<>());
                anos = this.answer.get(index_year);
            }

            List<Answer> ans = anos.get(index_mes);
            if(ans == null){
                anos.put(index_mes, new ArrayList<>());
                ans = anos.get(index_mes);
            }

            Answer a = (Answer) tmp;
            ans.add(a);
        }


    }


}
