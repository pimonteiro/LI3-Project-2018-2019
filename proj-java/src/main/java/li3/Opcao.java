package li3;

public class Opcao {

    private String tag;
    private String linha;

    public Opcao(String linha, String tag){
        this.tag = tag;
        this.linha = linha;
    }

    public Opcao(Opcao a){
        this.tag = a.getTag();
        this.linha = a.getLinha();
    }

    public String getTag(){
        return this.tag;
    }

    public String getLinha(){
        return this.linha;
    }

    @Override
    public String toString(){
        return this.linha + this.tag;
    }

    @Override
    public Opcao clone(){
        return new Opcao(this);
    }
}
