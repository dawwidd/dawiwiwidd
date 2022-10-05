from fhirpy import SyncFHIRClient

HAPI_BASE_URL = "http://localhost:8080/baseR4/"

client = SyncFHIRClient(HAPI_BASE_URL)

patientResources = client.resources('Patient')
observationResources = client.resources('Observation')
medicationRequestResources = client.resources('MedicationRequest');
# resources = resources.search(name="David").limit(10).sort('name')
patients = patientResources.fetch()
observations = observationResources.fetch()

# patient1 = patients.pop()

for patient in patients:
    print(patient['name'][0]["family"])

for observation in observations:
    print(observation["code"]["coding"][0]["display"])

print(len(patients), len(observations))


# for patient, observation in zip(patients, observations):
#     print(patient["name"][0]["family"], observation["code"]["coding"][0]["display"])