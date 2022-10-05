package main;
import java.util.Scanner;



public class Address
{
    Scanner sc = new Scanner(System.in);

    private String city, street, number;
    private boolean checkAddress(String c, String s, String n)
    {
        if(!c.matches("[a-zA-Z]+"))
        {
            return false;
        }

        if(!s.matches("[a-zA-Z]+"))
        {
            return false;
        }

        if(!n.matches("[0-9]+"))
        {
            return false;
        }
        return true;
    }


    Address(){}
    Address(String c, String s, String n)
    {
        while(true)
        {
            if(!checkAddress(c, s, n))
            {
                System.out.println("Niepoprawny adres, Wprowadz ponownie: ");
                c = sc.nextLine();
                s = sc.nextLine();
                n = sc.nextLine();
                continue;
            }
            this.city = c;
            this.street = s;
            this.number = n;
            break;
        }
    }


    public void setAddress(String c, String s, String n)
    {
        while(true)
        {
            if(!checkAddress(c, s, n))
            {
                System.out.println("Niepoprawny adres, Wprowadz ponownie: ");
                c = sc.nextLine();
                s = sc.nextLine();
                n = sc.nextLine();
                continue;
            }
            this.city = c;
            this.street = s;
            this.number = n;
            break;
        }
    }

    public void setCity(String c)
    {
        while(true)
        {
            if(!checkAddress(c, this.street, this.number))
            {
                System.out.println("Niepoprawne miasto, Wprowadz ponownie: ");
                c = sc.nextLine();
                continue;
            }
            this.city = c;
            break;
        }
    }

    public void setStreet(String s)
    {
        while(true)
        {
            if(!checkAddress(this.city, s, this.number))
            {
                System.out.println("Niepoprawna ulica, Wprowadz ponownie: ");
                s = sc.nextLine();
                continue;
            }
            this.street = s;
            break;
        }
    }

    public void setNumber(String n)
    {
        while(true)
        {
            if(!checkAddress(this.city, this.street, n))
            {
                System.out.println("Niepoprawny numer, Wprowadz ponownie: ");
                n = sc.nextLine();
                continue;
            }
            this.number = n;
            break;
        }
    }


    public Address getAddres(){ return this; }
    public String getCity(){ return this.city; }
    public String getStreet(){ return this.street; }
    public String getNumber(){ return this.number; }

    public String getAddressString()
    {
        return this.city + " " + this.street + " " + this.number;
    }

}
