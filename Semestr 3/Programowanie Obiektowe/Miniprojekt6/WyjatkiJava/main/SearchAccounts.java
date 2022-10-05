package main;

import java.util.ArrayList;

//Zadania 7, 9. Dzieki interfejsom można wykorzystać poniższe funkcje w wielu różnych innych klasach, nie tylko w klasie Bank
public interface SearchAccounts {
    Account findByNumber(int number) throws AccountNotFoundException;

    ArrayList<Account> findAllCustomerAccounts(Customer cust) throws AccountNotFoundException;
}
