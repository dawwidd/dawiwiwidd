export class Patient {
    private id: string;
    private firstName: string;
    private lastName: string;
    private address: string;
    private dateOfBirth: string;

    constructor(
        id: string,
        firstName: string,
        lastName: string,
        address: string,
        dateOfBirth: string
    ) {
        this.id = id;
        this.firstName = firstName;
        this.lastName = lastName;
        this.address = address;
        this.dateOfBirth = dateOfBirth;
    }
}
