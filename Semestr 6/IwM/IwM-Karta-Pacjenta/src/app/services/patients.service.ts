import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { URL } from 'variables';

@Injectable({
    providedIn: 'root',
})
export class PatientsService {
    private getAllPatientsUrl = 'Patient/$everything';

    private getPatientUrlPrefix = 'Patient/';
    private getPatientUrlSuffix = '/$everything';

    constructor(private httpClient: HttpClient) {}

    public getAllPatients() {
        let response = this.httpClient.get<any>(URL + this.getAllPatientsUrl);
        return response;
    }

    public getPatient(id: number) {
        let response = this.httpClient.get<any>(
            URL + this.getPatientUrlPrefix + id + this.getPatientUrlSuffix
        );
        return response;
    }
}
