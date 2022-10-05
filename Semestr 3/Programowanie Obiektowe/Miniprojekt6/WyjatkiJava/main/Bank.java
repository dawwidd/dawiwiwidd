package main;

import java.util.ArrayList;

// Zadanie 8
public class Bank implements SearchAccounts, SearchCustomers
{
    ArrayList<Customer> customers = new ArrayList<Customer>();
    ArrayList<Account> accounts = new ArrayList<Account>();

    @Override
    public Account findByNumber(int num) throws AccountNotFoundException
    {
        for(Account a : accounts)
        {
            if(a.getNumber() == num) return a;
        }
        throw new AccountNotFoundException("Nie znaleziono konta o podanym numerze.", num);
    }

    @Override
    public ArrayList<Account> findAllCustomerAccounts(Customer cust) throws AccountNotFoundException
    {
        ArrayList<Account> cAccounts= new ArrayList<Account>();

        for(Account a : accounts)
        {
            if(a.getCustomer().equals(cust)) cAccounts.add(a);
        }
        throw new AccountNotFoundException("Nie znaleziono kont dla podanego klienta.");
    }

    @Override
    public Customer findByName(String name) throws CustomerNotFoundException
    {
        for(Customer c : customers)
        {
            if(c.getName().equals(name)) return c;
        }
        throw new CustomerNotFoundException("Nie znaleziono klienta o tym imieniu.", name);
    }

}
