package pl.put.poznan.transformer.logic;

/**
 * Making all letter in a given string a lowercase type
 *
 * @author Adrian
 */
public class LowerCaseDecorator extends Decorator{

    public LowerCaseDecorator(String text) {
        this.text = text;
    }

    @Override
    public String decore() {
        return this.text.toLowerCase();
    }
}