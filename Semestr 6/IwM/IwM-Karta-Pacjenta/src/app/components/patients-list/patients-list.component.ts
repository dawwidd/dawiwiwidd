import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { Patient } from 'src/app/models/patient.model';
import { PatientsService } from 'src/app/services/patients.service';

@Component({
    selector: 'app-patients-list',
    templateUrl: './patients-list.component.html',
    styleUrls: ['./patients-list.component.scss'],
})
export class PatientsListComponent implements OnInit {
    public patients: Patient[] = [];
    public patient = [];

    constructor(private patientsService: PatientsService) {}

    ngOnInit(): void {
        // this.getAllPatientsData();

        let i = 0;
        while (i < 15) {
            this.getPatientData(i);
            i++;
        }
    }

    private getAllPatientsData() {
        this.patientsService.getAllPatients().subscribe((res) => {
            for (let entry of res['entry']) {
                if (entry['resourceType'] == 'Patient') {
                    let id = entry['id'];
                    let firstName = entry['name'][0]['given'][0];
                    let lastName = entry['name'][0]['family'];
                    let patient = new Patient(id, firstName, lastName, '', '');
                    console.log(firstName);
                }
            }
        });
    }

    private getPatientData(patientId: number) {
        this.patientsService.getPatient(patientId).subscribe((res) => {
            if (res['entry'] != undefined && res['entry'].length != 0) {
                // console.log(res['entry']);
                for (let entry of res['entry']) {
                    if (entry['resourceType'] === 'Patient') {
                        let id = entry['id'];
                        let firstName = entry['name'][0]['given'][0];
                        let lastName = entry['name'][0]['family'];
                        let patient = new Patient(
                            id,
                            firstName,
                            lastName,
                            '',
                            ''
                        );
                        console.log(firstName);
                    }
                }
            }
            // console.log(this.patient);
        });
    }
}
