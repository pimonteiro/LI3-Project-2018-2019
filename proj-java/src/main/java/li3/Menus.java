package li3;

import java.util.HashMap;

public class Menus {

    private HashMap<Integer,Menu> menus;

    public Menus(){
        this.menus = new HashMap<>();
    }


    //TODO Should i put the Menu.clone() ??
    public void addMenu(int i, Menu m){
        this.menus.put(i, m);
    }

    public Menu getMenu(int i){
        return this.menus.get(i);
    }
}
