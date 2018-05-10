import java.util.ArrayList;
import java.util.List;

public class Query5 {
    public void get_user_info(Main_Struct com, long id) throws NoProfileFound{
        List<Integer> post_history = new ArrayList<>(10);

        Profile p = com.getProfile(id);
        StringBuilder aboutme = new StringBuilder();
        aboutme.append(p.getAbout_me());

        //TODO Get 10 latest posts
    }
}
