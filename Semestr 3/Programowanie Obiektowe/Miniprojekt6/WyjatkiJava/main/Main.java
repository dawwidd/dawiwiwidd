package main;

public class Main {
    public static void main(String[] args) throws CustomerNotFoundException, AccountNotFoundException, AccountLoginFailedException
    {
        // Zadanie 10
        Bank bank1 = new Bank();

        Address adres1 = new Address("Myslowice", "Slunska", "35");
        Address adres2 = new Address("Pacanow", "Kozia", "66");

        Customer klient1 = new Customer("Zbyszek", adres1, 10371984);
        Customer klient2 = new Customer("Krzysiek", adres2, 10376544);

        Account account1 = new Account(123456, klient1, 1234, "Zbyszek37");
        Account account2 = new Account(654321, klient2, 4321, "Kszychu73");

        bank1.customers.add(klient1);
        bank1.customers.add(klient2);

        bank1.accounts.add(account1);
        bank1.accounts.add(account2);

        try
        {
            account1.login("Zbyszek37", 1234);
            account2.login("Kszychu73", 4321);
            //account2.login("ZenekM4rtyn1uk", 7878);
        }
        catch(AccountLoginFailedException lgFld)
        {
            lgFld.printStackTrace();
        }
        
        try
        {
            bank1.findByNumber(123456);
            bank1.findByNumber(654321);
            // bank1.findByNumber(777777);
        }
        catch(AccountNotFoundException accNotFnd)
        {
            accNotFnd.printStackTrace();
        }

        try
        {
            bank1.findByName("Zbyszek");
            bank1.findByName("Krzysiek");
            //bank1.findByName("Zenon");
        }
        catch(CustomerNotFoundException custNotFnd)
        {
            custNotFnd.printStackTrace();

            // Zadanie 11
            // throw custNotFnd; //Wypisane ślady stosu są identyczne

            // Zadanie 12
            custNotFnd.fillInStackTrace();
            throw custNotFnd; // użycie fillInStackTrace() powoduje wypisanie tylko miejsca w którym metoda ta została wywołana, pomijając dokładne detale i funkcje, które przyczyniły się do błędu/wyjątku.
        }
    }   
}
