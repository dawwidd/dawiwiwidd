package main;

import java.util.Scanner;

//Zadania 4,5
public class Account
{
    Scanner sc = new Scanner(System.in);

    private int accountNumber;
    private Customer owner;
    private double balance;
    private int password;
    private String login;
    
    public Account(){}
    public Account(int n, Customer c, int p, String l)
    {
        this.accountNumber = n;
        this.owner = c;
        this.password = p;
        this.login = l;
    }

    public void login() throws AccountLoginFailedException
    {
        System.out.println("Login: ");
        String l = sc.nextLine();
        System.out.println("Password: ");
        int p = sc.nextInt();

        if(!(l.equals(this.login)) || p != this.password) throw new AccountLoginFailedException("Bledny login lub haslo", l ,p);
    }

    public void login(String l, int p) throws AccountLoginFailedException
    {
        if(!(l.equals(this.login)) || p != this.password) throw new AccountLoginFailedException("Bledny login lub haslo", l ,p);
    }

    public void setAccountNumber(int an){ this.accountNumber = an; }
    public void setOwner(Customer c){ this.owner = c; }
    public void setBalance(double b){ this.balance = b;}
    public void setPassword(int p){ this.password = p; }
    public void setLogin(String l){ this.login = l; }

    public int getNumber() { return this.accountNumber; }
    public Customer getCustomer() { return this.owner;}
    public double getBalance() { return this.balance; }
    public int getPassword() { return this.password; }
    public String getLogin() { return this.login; }

    public double withdraw(double amount)
    {
        this.balance-=amount;
        return amount;
    }
}
