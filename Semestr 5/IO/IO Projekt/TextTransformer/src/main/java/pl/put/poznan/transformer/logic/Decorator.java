package pl.put.poznan.transformer.logic;

/**
 * Abstract class for decorating text
 *
 * @author Dawid
 */
public abstract class Decorator implements TextTransformer {

    public String text;

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }
}
