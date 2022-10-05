package put.io.testing.mocks;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.mockito.InOrder;
import org.mockito.invocation.InvocationOnMock;
import org.mockito.stubbing.Answer;
import put.io.students.fancylibrary.service.FancyService;

import java.net.ConnectException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.stream.IntStream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.ArgumentMatchers.*;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.*;

public class ExpenseManagerTest {

    private static ArrayList<Expense> expenses;

    @BeforeAll
    static void setup() {
        expenses = new ArrayList<>();
        Expense expense = new Expense();
        expense.setAmount(3);
        IntStream.range(0, 3).forEach(i -> expenses.add(expense));
    }

    @Test
    void testCalculateTotal() {
        IExpenseRepository expenseRepositoryMocked = mock(IExpenseRepository.class);

        when(expenseRepositoryMocked.getExpenses()).thenReturn(expenses);

        FancyService fancyServiceMocked = mock(FancyService.class);

        ExpenseManager expenseManager = new ExpenseManager(expenseRepositoryMocked, fancyServiceMocked);

        InOrder inOrder = inOrder(expenseRepositoryMocked);

        assertEquals(9, expenseManager.calculateTotal());
    }

    @Test
    void testCalculateTotalForCategory() {
        IExpenseRepository expenseRepositoryMocked = mock(IExpenseRepository.class);
        FancyService fancyServiceMocked = mock(FancyService.class);

        when(expenseRepositoryMocked.getExpensesByCategory(anyString())).thenReturn(Collections.emptyList());
        when(expenseRepositoryMocked.getExpensesByCategory("Home")).thenReturn(expenses);
        when(expenseRepositoryMocked.getExpensesByCategory("Car")).thenReturn(expenses);

        ExpenseManager expenseManager = new ExpenseManager(expenseRepositoryMocked, fancyServiceMocked);

        assertEquals(0, expenseManager.calculateTotalForCategory("Sport"));
        assertEquals(0, expenseManager.calculateTotalForCategory("Food"));
        assertEquals(9, expenseManager.calculateTotalForCategory("Car"));
        assertEquals(9, expenseManager.calculateTotalForCategory("Home"));
    }

    @Test
    void testCalculateTotalInDollars() throws ConnectException {
        IExpenseRepository expenseRepositoryMocked = mock(IExpenseRepository.class);
        FancyService fancyServiceMocked = mock(FancyService.class);

        when(expenseRepositoryMocked.getExpenses()).thenReturn(expenses);
        ExpenseManager expenseManager = new ExpenseManager(expenseRepositoryMocked, fancyServiceMocked);
        when(fancyServiceMocked.convert(anyDouble(),eq("PLN"),eq("USD"))).thenThrow(new ConnectException());
        when(fancyServiceMocked.convert(anyDouble(), eq("PLN"), eq("USD"))).thenAnswer(new Answer<Object>() {

            public Object answer(InvocationOnMock invocationOnMock) throws Throwable {
                Object[] args = invocationOnMock.getArguments();
                return (Double) args[0] * 4;
            }
        });
        expenseManager.calculateTotalInDollars();
        assertEquals(36, expenseManager.calculateTotalInDollars());
    }
}