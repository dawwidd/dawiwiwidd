package main;

public class CustomerNotFoundException extends Exception{
    static final long serialVersionUID = 1L;
    private String name;

    CustomerNotFoundException(){}
    CustomerNotFoundException(String errorMsg)
    {
        super(errorMsg);
    }
    CustomerNotFoundException(String errorMsg, String n)
    {
        super(errorMsg);
        name = n;
    }

    void setName(String n){ this.name = n; }

    String getName(){ return this.name; }
}
