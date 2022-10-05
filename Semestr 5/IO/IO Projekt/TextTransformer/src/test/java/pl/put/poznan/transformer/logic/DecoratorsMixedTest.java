package pl.put.poznan.transformer.logic;


import org.junit.jupiter.api.Test;


import static org.junit.jupiter.api.Assertions.*;

class DecoratorsMixedTest {
    private InverseDecorator id;
    private FullToShortcutDecorator fs;
    private LatexDecorator ld;
    private RepeatedDeletedDecorator rd;
    private ShortcutFullNameDecorator fn;
    private CapitaliseDecorator cd;
    private UpperCaseDecorator uc;
    private LowerCaseDecorator lw;


    public void set1(){
        id = new InverseDecorator("ala ala kola");
        rd = new RepeatedDeletedDecorator((id.decore()));
    }

    @Test
    void testRepeatReverse() {
        set1();
        assertEquals("ala alok",rd.decore());
    }

    void set2(){
        fs = new FullToShortcutDecorator("Profesor Profesor");
        rd = new RepeatedDeletedDecorator(fs.decore());
    }

    @Test
    void testShortRepeat() {
        set2();
        assertEquals("Prof.",rd.decore());
    }

    void set3(){
        id = new InverseDecorator("Roseforp");
        fs= new FullToShortcutDecorator(id.decore());
    }

    @Test
    void testShortInverse() {
        set3();
        assertEquals("Prof.",fs.decore());
    }

    void set4(){
        ld = new LatexDecorator("%‡<");
        id = new InverseDecorator(ld.decore());
    }

    @Test
    void testLatexInverse() {
        ld = new LatexDecorator("%‡<");
        id = new InverseDecorator(ld.decore());
        assertEquals("sseltxet\\gadd\\%\\",id.decore());
    }

    void set5(){

    }

    @Test
    void testFullRepeat() {
        fn = new ShortcutFullNameDecorator("Prof. Prof.");
        rd = new RepeatedDeletedDecorator(fn.decore());
        assertEquals("Profesor",rd.decore());
    }

    void set6(){
        ld = new LatexDecorator("§ § § ¶");
        rd = new RepeatedDeletedDecorator(ld.decore());
    }

    @Test
    void testLatexRepeat() {
        set6();
        assertEquals("\\S \\S \\P",rd.decore());
    }

    void set7(){
        fn = new ShortcutFullNameDecorator("Prof. Prof.");
        rd = new RepeatedDeletedDecorator(fn.decore());
        uc = new UpperCaseDecorator(rd.decore());
    }

    @Test
    void testShortRepeatUpper() {
        set7();
        assertEquals("PROFESOR",uc.decore());
    }

    void set8(){
        fn = new ShortcutFullNameDecorator("Prof. Prof.");
        rd = new RepeatedDeletedDecorator(fn.decore());
        id = new InverseDecorator(rd.decore());
    }

    @Test
    void testShortRepeatInverse() {
        set8();
        assertEquals("Roseforp",id.decore());
    }

    void set9(){
        fn = new ShortcutFullNameDecorator("Profesor Profesor");
        rd = new RepeatedDeletedDecorator(fn.decore());
        lw = new LowerCaseDecorator(rd.decore());
    }

    @Test
    void testShortRepeatLower() {
        set9();
        assertEquals("profesor",lw.decore());
    }

    void set10(){
        ld = new LatexDecorator("¶ ™");
        uc = new UpperCaseDecorator(ld.decore());
    }

    @Test
    void testLatexUpper() {
        set10();
        assertEquals("\\P \\TEXTTRADEMARK",uc.decore());
    }

    void set11(){
        ld = new LatexDecorator("¶ ™");
        uc = new UpperCaseDecorator(ld.decore());
        id = new InverseDecorator(uc.decore());
    }

    @Test
    void testLatexUpperInverse() {
        set11();
        assertEquals("p\\ kRAMEDARTTXET\\",id.decore());
    }

}