import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { RouterModule, Routes } from '@angular/router';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { MainComponent } from './pages/main/main.component';
import { PatientsComponent } from './pages/patients/patients.component';
import { PatientsListComponent } from './components/patients-list/patients-list.component';
import { PatientsListElementComponent } from './components/patients-list-element/patients-list-element.component';

const appRoutes: Routes = [
    {
        path: '',
        component: MainComponent,
        children: [
            {
                path: 'patients',
                component: PatientsComponent,
            },
        ],
    },
];

@NgModule({
    declarations: [
        AppComponent,
        MainComponent,
        PatientsComponent,
        PatientsListComponent,
        PatientsListElementComponent,
    ],
    imports: [
        BrowserModule,
        AppRoutingModule,
        RouterModule.forRoot(appRoutes),
        HttpClientModule,
    ],
    providers: [],
    bootstrap: [AppComponent],
})
export class AppModule {}
