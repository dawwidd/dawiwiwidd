package pl.put.poznan.transformer.logic;

/**
 * Decorator class for converting text to UPPERCASE
 *
 * @author Dawid
 */
public class UpperCaseDecorator extends Decorator{

    public UpperCaseDecorator(String text) {
        this.text = text;
    }

    @Override
    public String decore() {
        return this.text.toUpperCase();
    }
}
