package li3;

import java.util.HashMap;

/**
 * Conjunto de menus, acediveis através de um HashMap.
 */
public class Menus {

    private HashMap<Integer,Menu> menus;

    public Menus(){
        this.menus = new HashMap<>();
    }

    /**
     * Adiciona um menu a este conjunto.
     * @param i indice a ser colocado
     * @param m Menu a ser adicionado
     */
    public void addMenu(int i, Menu m){
        this.menus.put(i, m.clone());
    }

    public Menu getMenu(int i){
        return this.menus.get(i);
    }
}
