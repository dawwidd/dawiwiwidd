package pl.put.poznan.transformer.logic;

/**
 * Making all letter in a given string a lowercase type
 *
 * @author Adrian
 */
public class RepeatedDeletedDecorator extends Decorator{

    public RepeatedDeletedDecorator(String text) {
        this.text = text;
    }






    @Override
    public String decore() {
        {
            String result= "";
            String[] words=text.split(" ");
            int len=words.length;
            for(int i=0;i<len-1;i++)
            {
                if(words[i].equals(words[i+1])) {
                    words[i+1] = "";
                }
            }
            for(int a=0;a<len;a++)
            {
                if(!words[a].equals("")) result += words[a] +" ";
            }
            return result.trim();
        }
    }
}
