package pl.put.poznan.transformer.logic;


import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;


import static org.junit.jupiter.api.Assertions.*;

class DecoratorsTest {
    private CapitaliseDecorator cd;
    private NumbersToTextDecorator nt;
    private UpperCaseDecorator uc;

    public String text="ala ma kota";

    public void setCd(){
        cd = new CapitaliseDecorator("ala ma kota");
    }

    @Test
    void testCapitaliseAll() {
        setCd();
        assertEquals("Ala Ma Kota",cd.decore());
    }

    void Partly(){
        cd = new CapitaliseDecorator("krzych Ma Kota");
    }

    @Test
    void testCapitalisePartly() {
        Partly();
        assertEquals("Krzych Ma Kota",cd.decore());
    }

    void AllCapitalize(){
        cd = new CapitaliseDecorator("Grzegorz Ma Kota");
    }

    @Test
    void testCapitalisNothing() {
        AllCapitalize();
        assertEquals("Grzegorz Ma Kota",cd.decore());
    }

    void SmallNumber(){
        nt = new NumbersToTextDecorator("1");
    }

    @Test
    void testAllNumber() {
        SmallNumber();
        assertEquals("jeden",nt.decore());
    }
    void MiddleNumber(){
        nt = new NumbersToTextDecorator("1123");
    }

    @Test
    void testMiddleNumber() {
        MiddleNumber();
        assertEquals("jeden tys. sto dwadzieścia trzy",nt.decore());
    }

    void BigNumber(){
        nt = new NumbersToTextDecorator("816247614");
    }

    @Test
    void testBigNumber() {
        BigNumber();
        assertEquals("osiemset siedemnaście mln. dwieście czterdzieści siedem tys. sześćset czternaście",nt.decore());
    }
    void AlltoUpper(){
        uc = new UpperCaseDecorator("ala ma kota");
    }

    @Test
    void testAllUpper() {
        AlltoUpper();
        assertEquals("ALA MA KOTA",uc.decore());
    }

    void PartlytoUpper(){
        uc = new UpperCaseDecorator("Ala Ma Kota");
    }

    @Test
    void testPartlyUpper() {
        PartlytoUpper();
        assertEquals("ALA MA KOTA",uc.decore());
    }

    void NothingtoUpper(){
        uc = new UpperCaseDecorator("ALA MA KOTA");
    }

    @Test
    void testNothingUpper() {
        NothingtoUpper();
        assertEquals("ALA MA KOTA",uc.decore());
    }
}