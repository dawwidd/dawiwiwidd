package put.io.testing.mocks;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

//import org.junit.*;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.mockito.*;

import put.io.students.fancylibrary.database.FancyDatabase;
import put.io.students.fancylibrary.database.IFancyDatabase;

import java.util.Collections;
import java.util.List;
import java.util.stream.IntStream;

public class ExpenseRepositoryTest {
    private ExpenseRepository expenseRepository;
    private List<Expense> expenses;

    @Test
    void testLoadExpenses(){
        myDatabase db = new myDatabase();
        expenseRepository = new ExpenseRepository(db);
        expenseRepository.loadExpenses();
        assertEquals(0, expenseRepository.getExpenses().size());
    }

    @Test
    void testLoadExpenses2(){
        //Tworzenie
        IFancyDatabase mockedDB = mock(IFancyDatabase.class);
        InOrder inOrder = inOrder(mockedDB);
        //Konfiguracja
        when(mockedDB.queryAll()).thenReturn(Collections.emptyList());
        //Interakcja
        expenseRepository = new ExpenseRepository(mockedDB);
        expenseRepository.loadExpenses();
        //Weryfikacja
        inOrder.verify(mockedDB).connect();
        inOrder.verify(mockedDB).queryAll();
        inOrder.verify(mockedDB).close();
        assertEquals(0, expenseRepository.getExpenses().size());
    }

    @Test
    void testSaveExpenses() {
        //Tworzenie
        IFancyDatabase mockedDB = mock(IFancyDatabase.class);
        InOrder inOrder = inOrder(mockedDB);
        //Konfiguracja
        when(mockedDB.queryAll()).thenReturn(Collections.emptyList());
        //Interakcja
        expenseRepository  = new ExpenseRepository(mockedDB);
        IntStream.range(0, 5).forEach(i -> expenseRepository.addExpense(new Expense()));
        expenseRepository.saveExpenses();
        //Weryfikacja

        inOrder.verify(mockedDB).connect();
        inOrder.verify(mockedDB, times(5)).persist(any(Expense.class));
        inOrder.verify(mockedDB).close();
    }

}