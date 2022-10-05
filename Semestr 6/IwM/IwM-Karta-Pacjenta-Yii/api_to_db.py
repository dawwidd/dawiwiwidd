import asyncio
from urllib.request import urlopen
from fhirpy import AsyncFHIRClient
import json
import sqlite3

from numpy import insert

class Patient:
    TABLE_NAME = 'patient'
    
    def __init__(self, data) -> None:
        self.identifier = data['id'] # data['identifier'][0]['system']
        self.name = f"{data['name'][0]['family']} {data['name'][0]['given'][0]}"
        self.gender = data['gender'] if 'gender' in data.keys() else "no data"
        self.birthDate = data['birthDate']
    
    def __repr__(self) -> str:
        reprStr = f"[{self.identifier}] Name: {self.name}, Gender: {self.gender}, Birthdate: {self.birthDate}"
        return reprStr
    
    def save(self):
        conn = sqlite3.connect('fhir.db')
        cursor = conn.cursor()
        insertQuery = """INSERT INTO
        patient(
            identifier,
            name,
            gender,
            birthDate
        )
        values(?,?,?,?)
        """
        cursor.execute(insertQuery, (
                self.identifier,
                self.name,
                self.gender,
                self.birthDate
            )
        )
        conn.commit()
        conn.close()

class Observation:
    TABLE_NAME = 'observation'
    
    def __init__(self, data) -> None:
        self.date = data['effectiveDateTime']
        self.patientId = data['subject']['reference'].split('/')[1]
        self.coding = data['code']['text']
        self.value = data['valueQuantity']['value']
        self.unit = data['valueQuantity']['unit']
    
    def __repr__(self) -> str:
        reprStr = f"""{self.coding} {self.value} {self.unit} {self.date} {self.patientId}"""
        return reprStr
    
    def save(self):
        conn = sqlite3.connect('fhir.db')
        cursor = conn.cursor()
        insertQuery = """INSERT INTO
        observation(
            coding,
            value,
            unit,
            date,
            patientIdentifier
        )
        values(?,?,?,?,?)
        """
        cursor.execute(insertQuery,(
                self.coding,
                self.value,
                self.unit,
                self.date,
                self.patientId
                )
            )
        conn.commit()
        conn.close()
        
        
class MedicationStatement:
    TABLE_NAME = 'medicationStatement'
    
    def __init__(self, data) -> None:
        self.concept = data['medicationCodeableConcept']['coding'][0]['display']
        self.patientId = data['subject']['reference'].split('/')[1]
    
    def __repr__(self) -> str:
        reprStr = f"""{self.concept} {self.patientId}"""
        return reprStr

    def save(self):
        conn = sqlite3.connect('fhir.db')
        cursor = conn.cursor()
        insertQuery = """INSERT INTO
        medicationStatement(
            concept,
            patientId
        )
        values(?,?)
        """
        cursor.execute(insertQuery,(
                self.concept,
                self.patientId
                )
            )
        conn.commit()
        conn.close()
        
        
class Factory:
    PATIENT = 'Patient'
    OBSERVATION = 'Observation'
    
    def createObject(self, dictObj):
        if dictObj['resourceType'] == self.PATIENT:
            patient = Patient(dictObj)
            return patient
        elif dictObj['resourceType'] == self.OBSERVATION:
            observation = Observation(dictObj)
            return observation

class JsonApiClient:
    
    def __init__(self) -> None:
        pass

    def getJson(self, url):
        response = urlopen(url)
        self.json = json.loads(response.read())   
        return self.json


class ApiClient:
        
    def __init__(self, baseURL) -> None:
        self.baseURL = baseURL
        self.client = AsyncFHIRClient(
            self.baseURL,
            authorization='Bearer TOKEN',
        )
    
    def getPatients(self) -> list:
        loop = asyncio.get_event_loop()
        # loop = asyncio.new_event_loop()
        # asyncio.set_event_loop(loop)

        patients = loop.run_until_complete(self.__fetchPatients())
        return patients
        
    async def __fetchPatients(self) ->list:
        # Search for patients
        resources = self.client.resources('Patient')  # Return lazy search set
        patients = await resources.fetch()
        
        patientsList = []
        for p in patients:
            patientsList.append(p.serialize())
        return patientsList
    
def apiFun():
    
    # apiClient = ApiClient('http://hapi.fhir.org/baseR4/')
    # factory = Factory()

    # patientsList = apiClient.getPatients()
    # patients = []
    # print(patientsList)
    # for patient in patientsList:
    #     print(patient)
    #     patients.append(factory.createObject(patient))
    #     print(patients[-1])
    #     print()
    pass

def fetchObservationToDB(urlToFetch):
    jsonApiClient = JsonApiClient()
    observations = jsonApiClient.getJson(urlToFetch)
    for observation in observations['entry']:
        if observation['fullUrl']:
            observation = jsonApiClient.getJson(observation['fullUrl'] + '?_format=json') 
            # print(observation)  
            try:    
                observation = Observation(observation)
            except KeyError:
                continue
            print(observation)
            print()
            observation.save()

def fetchPatientsToDB(patientIdentifier):
    jsonApiClient = JsonApiClient()
    urlToFetch = f"https://hapi.fhir.org/baseR4/Patient/{patientIdentifier}?_format=json"
    patient = jsonApiClient.getJson(urlToFetch)
    try:
        patient = Patient(patient)
        print(patient)
        print()
        patient.save()
    except KeyError:
        pass


# def fetchMedicationStatementToDB(patientIdentifier):
#     jsonApiClient = JsonApiClient()
#     urlToFetch = f"http://hapi.fhir.org/baseR4/MedicationStatement?_pretty=true&patient={patientIdentifier}&_format=json"
#     medicationStatement = jsonApiClient.getJson(urlToFetch)
#     try:
#         medicationStatement = MedicationStatement(medicationStatement)
#         print(medicationStatement)
#         print()
#         medicationStatement.save()
#     except KeyError:
#         pass
    
    
def fetchMedicationStatementToDB(patientIdentifier):
    urlToFetch = f"http://hapi.fhir.org/baseR4/MedicationStatement?_pretty=true&patient={patientIdentifier}&_format=json"
    jsonApiClient = JsonApiClient()
    medicationStatements = jsonApiClient.getJson(urlToFetch)
    if 'entry' in medicationStatements.keys():
        for medicationStatement in medicationStatements['entry']:
            if medicationStatement['fullUrl']:
                medicationStatement = jsonApiClient.getJson(medicationStatement['fullUrl'] + '?_format=json') 
                # print(medicationStatement)  
                try:    
                    medicationStatement = MedicationStatement(medicationStatement)
                except KeyError:
                    continue
                print(medicationStatement)
                print()
                medicationStatement.save()
    
if __name__ == '__main__':
    # fetchObservationToDB('http://hapi.fhir.org/baseR4?_getpages=ccbd8487-c57a-4f2a-938d-fa819954d196&_pretty=true&_count=1000&_getpagesoffset=500&_bundletype=searchset&_format=json')
    patientIdentifierList = [1454817,1459879,1459976,1836962,1906371,1906395,1906415,1906436,1906479,1906500,1906541,1906564,1906606,1906625,1906646,1906667,1906688,1906732,1906751,1906793,1906819,1906839,1906859,1906901,1906921,1906964,1906984,1907045,1907053,1907078,1907090,1907111,1907153,1907193,1993934,2374044,2644914,2664987,2665065,2665143,2666038,2666137,2666898,2666976,2706021,2706708,2706786,2707699]
    for pId in patientIdentifierList:
    #     fetchObservationToDB(pId)
        fetchMedicationStatementToDB(pId)
