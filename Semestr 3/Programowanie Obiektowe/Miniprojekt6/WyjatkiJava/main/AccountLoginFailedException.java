package main;

//Zadanie 6
public class AccountLoginFailedException extends Exception{
    static final long serialVersionUID = 1L;
    
    private int password;
    private String login;

    AccountLoginFailedException(){}
    AccountLoginFailedException(String errorMsg, String l, int passwd)
    {
        super(errorMsg);
        login = l;
        password = passwd;
    }

    void setLogin(String l){ this.login = l; }
    void setPassword(int p){ this.password = p; }
    
    String getLogin(){ return this.login; }
    int getPassword(){ return this.password; }
}
