package li3;

import java.util.ArrayList;
import java.util.List;

public class Menu {
    private String title;
    private ArrayList<Opcao> linhas;

    public Menu(String title, List<Opcao> linhas){
        this.title = title;
        this.linhas = new ArrayList<>(linhas);
    }

    public void show(){
        System.out.print(this.title);
        this.linhas.forEach(o -> System.out.println(o.toString()));
    }

}
