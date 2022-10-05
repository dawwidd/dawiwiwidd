package pl.put.poznan.transformer.logic;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.jupiter.api.BeforeAll;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.mockito.MockitoAnnotations;
import pl.put.poznan.transformer.logic.*;
import pl.put.poznan.transformer.rest.TextTransformerController;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;
import static org.mockito.Mockito.*;

public class MockTests {

    @Before
    public void init(){
        MockitoAnnotations.initMocks(this);
    }

    @Test
    public void UpperCaseDecoratorMockTest() {
        UpperCaseDecorator decorator = mock(UpperCaseDecorator.class, withSettings().useConstructor("uppercase text"));

        when(decorator.decore()).thenReturn("UPPERCASE TEXT");

        Assert.assertEquals(decorator.decore(), new UpperCaseDecorator("uppercase text").decore());
    }

    @Test
    public void LowerCaseDecoratorTest() {
        LowerCaseDecorator decorator = mock(LowerCaseDecorator.class, withSettings().useConstructor("lOweRcaSe teXt"));

        when(decorator.decore()).thenReturn("lowercase text");

        Assert.assertEquals(decorator.decore(), new LowerCaseDecorator("lOweRcaSe teXt").decore());
    }

    @Test
    public void InverseDecoratorMockTest() {
        InverseDecorator decorator = mock(InverseDecorator.class, withSettings().useConstructor("inVersEd teXt"));

        when(decorator.decore()).thenReturn("deSrevNi txEt");

        Assert.assertEquals(decorator.decore(), new InverseDecorator("inVersEd teXt").decore());
    }

    @Test
    public void LatexDecoratorMockTest() {
        LatexDecorator decorator = mock(LatexDecorator.class, withSettings().useConstructor("©ⓐ¿®†"));

        when(decorator.decore()).thenReturn("\\copyright\\textcircled{a}\\textquestiondown\\textregistered\\dag");

        Assert.assertEquals(decorator.decore(), new LatexDecorator("©ⓐ¿®†").decore());
    }

    @Test
    public void NumbersToTextDecoratorMockTest() {
        NumbersToTextDecorator decorator = mock(NumbersToTextDecorator.class, withSettings().useConstructor("2137"));

        when(decorator.decore()).thenReturn("dwa tys. sto trzydzieści siedem");

        Assert.assertEquals(decorator.decore(), new NumbersToTextDecorator("2137").decore());
    }

    @Test
    public void RepeatedDeletedDecoratorMockTest() {
        RepeatedDeletedDecorator decorator = mock(RepeatedDeletedDecorator.class, withSettings().useConstructor("Gimme gimme gimme a man after midnight"));

        when(decorator.decore()).thenReturn("Gimme gimme a man after midnight");

        Assert.assertEquals(decorator.decore(), new RepeatedDeletedDecorator("Gimme gimme gimme a man after midnight").decore());
    }

    @Test
    public void CapitaliseDecoratorMockTest() {
        CapitaliseDecorator decorator = mock(CapitaliseDecorator.class, withSettings().useConstructor("jAN kOWALSKI"));

        when(decorator.decore()).thenReturn("Jan Kowalski");

        Assert.assertEquals(decorator.decore(), new CapitaliseDecorator("jAN kOWALSKI").decore());
    }

    @Test
    public void FullToShortcutDecoratorMockTest() {
        FullToShortcutDecorator decorator = mock(FullToShortcutDecorator.class, withSettings().useConstructor("Pieczywo to na przykład chleb i bułki"));

        when(decorator.decore()).thenReturn("Pieczywo to np. chleb i bułki");

        Assert.assertEquals(decorator.decore(), new FullToShortcutDecorator("Pieczywo to na przykład chleb i bułki").decore());
    }

    @Test
    public void ShortcutFullNameDecoratorMockTest() {
        ShortcutFullNameDecorator decorator = mock(ShortcutFullNameDecorator.class, withSettings().useConstructor("Pieczywo to np. chleb i bułki"));

        when(decorator.decore()).thenReturn("Pieczywo to na przykład chleb i bułki");

        Assert.assertEquals(decorator.decore(), new ShortcutFullNameDecorator("Pieczywo to np. chleb i bułki").decore());
    }

    @Test
    public void ShortcutFullNameDecoratorMockTest2() {
        ShortcutFullNameDecorator decorator = mock(ShortcutFullNameDecorator.class, withSettings().useConstructor("mgr dr prof."));

        when(decorator.decore()).thenReturn("magister doktor profesor");

        Assert.assertEquals(decorator.decore(), new ShortcutFullNameDecorator("mgr dr prof.").decore());
    }
}
