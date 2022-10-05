package put.io.testing.audiobooks;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

//5.1 White-box
//5.2 4

class AudiobookPriceCalculatorTest {

    @Test
    public void SubscriberTest(){
        Customer klient = new Customer("Dawid", Customer.LoyaltyLevel.SILVER,true);
        Audiobook audiobook = new Audiobook("Krew Elfów",100);
        AudiobookPriceCalculator kalkulator = new AudiobookPriceCalculator();
        assertEquals(0,kalkulator.calculate(klient,audiobook));
    }
    @Test
    public void SilverTest(){
        Customer klient = new Customer("Arek", Customer.LoyaltyLevel.SILVER,false);
        Audiobook audiobook = new Audiobook("Czas Pogardy",100);
        AudiobookPriceCalculator kalkulator = new AudiobookPriceCalculator();
        assertEquals(90,kalkulator.calculate(klient,audiobook));
    }
    @Test
    public void GoldTest(){
        Customer klient = new Customer("Janusz", Customer.LoyaltyLevel.GOLD,false);
        Audiobook audiobook = new Audiobook("Chrzest Ognia",100);
        AudiobookPriceCalculator kalkulator = new AudiobookPriceCalculator();
        assertEquals(80,kalkulator.calculate(klient,audiobook));
    }
    @Test
    public void StandardTest(){
        Customer klient = new Customer("Dima", Customer.LoyaltyLevel.STANDARD,false);
        Audiobook audiobook = new Audiobook("Wieża Jaskółki",100);
        AudiobookPriceCalculator kalkulator = new AudiobookPriceCalculator();
        assertEquals(100,kalkulator.calculate(klient,audiobook));
    }
}