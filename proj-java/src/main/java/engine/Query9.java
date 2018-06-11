package engine;

import common.Comparators.PostCreationDateComparator;
import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;

import java.util.*;
import java.util.stream.Collectors;

public class Query9 {

    private static void insert_post_ordered(TreeSet<Post> seq, Post q){
        seq.add(q);
    }

    public static List<Long> bothParticipated(Main_Struct com, int N, long id1, long id2) throws
                                                                                          NoProfileFoundException,
                                                                                          NoPostFoundException{
        Profile p1 = com.getProfile(id1);
        if(p1.getN_posts() == 0) return new ArrayList<>();
        Profile p2 = com.getProfile(id2);
        if(p2.getN_posts() == 0) return new ArrayList<>();

        TreeSet<Post> posts = p1.getPosts();
        Iterator<Post> it = posts.iterator();

        TreeSet<Post> ret = new TreeSet<>(new PostCreationDateComparator());

        while(it.hasNext()){
            Post p = (Post) it.next();
            Question q;
            if(p instanceof Answer){
                Answer a = (Answer) p;
                q = (Question) com.getPost(a.getParent_id());
                if(q.getOwner_id() == id2){
                    insert_post_ordered(ret, q);
                    continue; //Continua pois se há já algo em comum, nao vale a pena verificar mais
                }
            }else{
                q = (Question) p;
            }

            //Answers de uma Question
            Map<Long,Answer> answers = q.getAnswers();
            for(Answer a : answers.values()){
                if(a.getOwner_id() == id2){ //Adiciona apenas a Pergunta
                    insert_post_ordered(ret, com.getPost(a.getParent_id()));
                    continue; //Continua pois é inutil verificar as outras respostas, os utilizadores ja tem este Post em comum
                }
            }
        }
        return ret.stream().map(Post::getId).limit(N).collect(Collectors.toList());
    }
}
