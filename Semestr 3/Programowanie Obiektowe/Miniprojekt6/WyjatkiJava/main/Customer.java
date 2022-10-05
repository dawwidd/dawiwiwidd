package main;


//Zadania 2, 3
public class Customer {
    private String name;
    private Address address;
    private int pesel;


    public Customer(){};
    public Customer(String s, Address a, int p)
    {
        this.name = s;
        this.address = a;
        this.pesel = p;
    }

    public void setName(String n) { this.name = n; }
    public void setAddress(Address a) { this.address = a; }
    public void setPesel(int p) { this.pesel = p; }

    public String getName(){ return this.name; }
    public Address getAddress(){ return this.address; }
    public int getPesel(){ return this.pesel; }

    // Adnotacja @Override służy do przesłonięcia metody z klasy macierzystej. Nie jest ona konieczna, jest jednak informacją dla programisty i kompilatora.
    // Dzięki tej adnotacji kompilator wie, że metoda ta jest przesłaniana, a nie jest to nowa, niezależna metoda.
    @Override
    public boolean equals(Object c)
    {
        return this.name.equals(((Customer) c).getName());
    }
}
