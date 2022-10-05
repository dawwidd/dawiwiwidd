package main;


public class AccountNotFoundException extends Exception{
    static final long serialVersionUID = 1L;
    private int accountNumber;

    AccountNotFoundException(){}
    AccountNotFoundException(String errorMsg)
    {
        super(errorMsg);
    }
    AccountNotFoundException(String errorMsg, int an)
    {
        super(errorMsg);
        accountNumber = an;
    }

    void setAccountNumber(int an)
    {
        this.accountNumber = an;
    }

    int getAccountNumber()
    {
        return this.accountNumber;
    }
}
