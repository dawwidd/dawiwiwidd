package main;

//Zadania 7, 9. Dzieki interfejsom można wykorzystać poniższe funkcje w wielu różnych innych klasach, nie tylko w klasie Bank
public interface SearchCustomers {
    Customer findByName(String name) throws CustomerNotFoundException;
}
