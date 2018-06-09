package engine;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;


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


    public static Main_Struct parse(String path){

        Main_Struct ms = new Main_Struct();

        SAXParserFactory parserFactor = SAXParserFactory.newInstance();
        parserFactor.setNamespaceAware(true);

        try{
            SAXParser parser = parserFactor.newSAXParser();

            XMLReader reader = parser.getXMLReader();

            reader.setContentHandler(new UserHandler(ms));
            reader.parse(convertToFileURL(path));

            //reader.parse(convertToFileURL("/home/herulume/Downloads/ubuntu/Users.xml"));
            return ms;

        }catch(IOException | SAXException | ParserConfigurationException e){
            System.out.println(e.getMessage());
            return null;
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

    PostHandler(Main_Struct cum){
        lmao = cum;
    }

    @Override
    public void startElement(String namespaceURI, String localName, String qName, Attributes atts){
        if(atts.getLength() == 0) return;


    }

}
