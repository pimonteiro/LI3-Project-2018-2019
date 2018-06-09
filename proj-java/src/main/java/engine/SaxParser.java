package engine;

import li3.Main;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;


public class SaxParser {

    private static String convertToFileURL(String filename){
        String path = new File(filename).getAbsolutePath();
        if(File.separatorChar != '/'){
            path = path.replace(File.separatorChar, '/');
        }

        if(!path.startsWith("/")){
            path = "/" + path;
        }
        return "file:" + path;
    }

    /*public static void main(String[] args){
        Main_Struct s = SaxParser.multParse("/home/herulume/Downloads/ubuntu/");
    }*/

    public static Main_Struct multParse(String path){
        Main_Struct lmao = new Main_Struct();

        SaxParser.parse(path + "Posts.xml", lmao, 0);
        SaxParser.parse(path + "Users.xml", lmao, 1);
        SaxParser.parse(path + "Tags.xml", lmao, 2);

        return lmao;


    }

    private static void parse(String path, Main_Struct ms, int flag){

        SAXParserFactory parserFactor = SAXParserFactory.newInstance();
        parserFactor.setNamespaceAware(true);

        try{
            SAXParser parser = parserFactor.newSAXParser();

            XMLReader reader = parser.getXMLReader();
            if(flag == 0)
                reader.setContentHandler(new PostHandler(ms));
            if(flag == 1)
                reader.setContentHandler(new UserHandler(ms));
            if(flag == 2)
                reader.setContentHandler(new TagsHandler(ms));

            reader.parse(convertToFileURL(path));

        }catch(IOException | SAXException | ParserConfigurationException e){
            System.out.println(e.getMessage());
        }

    }
}


class UserHandler extends DefaultHandler {

    private Main_Struct lmao;


    UserHandler(Main_Struct cum){
        lmao = cum;
    }

    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts){
        if(atts.getLength() == 0) return;

        String about_me = atts.getValue("AboutMe");
        String name = atts.getValue("DisplayName");
        long id = Long.parseLong(atts.getValue("Id"));
        int reputation = Integer.parseInt(atts.getValue("Reputation"));

        Profile p = new Profile(about_me, name, id, reputation);
        lmao.addProfile(p);

    }

}


class PostHandler extends DefaultHandler {

    private Main_Struct lmao;
    private DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");

    PostHandler(Main_Struct cum){
        lmao = cum;
    }

    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts){
        if(atts.getLength() == 0) return;

        int type = Integer.parseInt(atts.getValue("PostTypeId"));

        if(type != 1 && type != 2) return;

        long id = Integer.parseInt(atts.getValue("Id"));
        long owner_id = Long.parseLong(atts.getValue("OwnerUserId"));
        long score = Long.parseLong(atts.getValue("Score"));
        long n_comments = Long.parseLong(atts.getValue("CommentCount"));


        StringBuilder sb = new StringBuilder(atts.getValue("CreationDate"));
        sb.delete(15, sb.length() - 1); // TODO check index
        String cd = sb.toString().replace('T', ' ');
        LocalDateTime creation_date = LocalDateTime.parse(cd, formatter);


        if(type == 2){

            long parent_id = Long.parseLong(atts.getValue("ParentId"));
            Answer a = new Answer(id, owner_id, score, creation_date, parent_id, n_comments);

            lmao.addAnswer(a);

        }

        if(type == 1){

            //TODO tags

            long n_answers = Long.parseLong(atts.getValue("AnswerCount"));
            String title = atts.getValue("Title");


            Question q = new Question(id, owner_id, score, creation_date, n_comments, title, n_answers);


            lmao.addQuestion(q);
        }

    }

}

class TagsHandler extends DefaultHandler {

    private Main_Struct lmao;

    TagsHandler(Main_Struct cum){
        lmao = cum;
    }

    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts){
        if(atts.getLength() == 0) return;

        long id = Long.parseLong(atts.getValue("Id"));
        String s = atts.getValue("TagName");

        lmao.addTag(id, s);
    }

}