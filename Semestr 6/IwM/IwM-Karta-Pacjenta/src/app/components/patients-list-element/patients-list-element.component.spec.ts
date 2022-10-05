import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PatientsListElementComponent } from './patients-list-element.component';

describe('PatientsListElementComponent', () => {
  let component: PatientsListElementComponent;
  let fixture: ComponentFixture<PatientsListElementComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ PatientsListElementComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(PatientsListElementComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
