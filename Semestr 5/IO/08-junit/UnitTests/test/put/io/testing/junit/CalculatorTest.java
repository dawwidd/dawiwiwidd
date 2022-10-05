package put.io.testing.junit;
import java.util.Random;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class CalculatorTest {

    private Calculator calculator;

    @BeforeEach
    public void SetUp(){
        calculator = new Calculator();
    }

    @Test
    public void addingTest(){
        //Calculator kalkulator = new Calculator();
        Random rand = new Random();
        for (int i = 0; i<5;i++){
            int x = rand.nextInt();
            int y = rand.nextInt();

            assertEquals(x+y,calculator.add(x,y));
        }

    }
    @Test
    public void multiplyingTest(){
        //Calculator kalkulator = new Calculator();
        Random rand = new Random();
        for (int i = 0; i<5;i++){
            int x = rand.nextInt();
            int y = rand.nextInt();

            assertEquals(x*y,calculator.multiply(x,y));
        }
    }
    @Test
    public void AddPosTest(){
        //Calculator kalkulator = new Calculator();
        Assertions.assertThrows(IllegalArgumentException.class,() ->{
            calculator.addPositiveNumbers(-3,5);
        });
    }
}

// Pytanie 3.1 Nie będzie działać
