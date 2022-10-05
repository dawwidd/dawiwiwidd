package put.io.testing.junit;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertEquals;

class FailureOrErrorTest {

    private Calculator calculator;

    @BeforeEach
    public void SetUp(){
        calculator = new Calculator();
    }

    @Test
    public void test1(){
        //Calculator kalkulator = new Calculator();
        Random rand = new Random();

        assertEquals(4,calculator.add(1,7));
    }

    @Test
    public void test2(){
        assertEquals(0, new Calculator().addPositiveNumbers(-1, -6));

        //4.1 test1 - failure, test2 - error
    }
    @Test
    public void test3(){
        try{
            assertEquals(6*3, 6+3);
        }catch (Exception a){
            System.out.println(a.getStackTrace());
        }
    }

}