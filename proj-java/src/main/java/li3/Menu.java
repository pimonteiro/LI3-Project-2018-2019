package li3;

import java.util.ArrayList;
import java.util.List;

/**
 * Menu constituido por um titulo e um conjuntos de linhas.
 */
public class Menu {

    private String title;
    private List<Opcao> linhas;

    public Menu(String title, List<Opcao> linhas){
        this.title = title;
        this.linhas = new ArrayList<>(linhas);
    }

    public Menu(Menu m){
        this.title = m.getTitle();
        this.linhas= m.getLinhas();
    }

    public String getTitle(){
        return this.title;
    }

    public List<Opcao> getLinhas(){
        ArrayList<Opcao> ret = new ArrayList<>();
        this.linhas.forEach(o -> ret.add(o.clone()));

        return ret;
    }

    public void setTitle(String title){
        this.title = title;
    }

    public void setLinhas(List<Opcao> l){
        this.linhas = new ArrayList<>();
        l.forEach(o -> this.linhas.add(o.clone()));
    }

    public Menu clone(){
        return new Menu(this);
    }

    /**
     * Metodo que imprime no ecrã este menu
     */
    public void show(){
        System.out.print(this.title);
        this.linhas.forEach(o -> System.out.println(o.toString()));
    }

}
