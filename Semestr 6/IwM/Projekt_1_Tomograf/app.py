from os import path
import streamlit as st
from CTScanner import *
from Image import *
from Algorithms import *
from Components import Components
from config import *
from dicomIO import dicomIO
import numpy as np

st.set_page_config(page_title="Symulacja tomografu")

C = Components()

C.sidebar()
# with st.form(key="form"):
#     x = st.time_input("Input:")
#     if st.form_submit_button("submit"):
#         st.warning(x)
#         print("inside form form if after buton")
        
if C.currentApplication == C.APPS["CT"]:
    C.headerCT()
    C.horizontalSeparator()
    colSelector, colUploader = st.columns([1,2])

    with colSelector:
        C.fileSelector(IMAGES_DIR)
        
    with colUploader:
        C.fileUploader(IMAGES_DIR)
    C.settings()
    C.imagePreview()
elif C.currentApplication == C.APPS["DICOM"]:
    C.headerDICOM()
    C.horizontalSeparator()

    colSelector, colUploader = st.columns([1,2])

    with colSelector:
        C.fileSelector(DICOMS_DIR)
        
    with colUploader:
        C.fileUploader(DICOMS_DIR)


    if st.button('Wczytaj'):
        dcm = dicomIO()
        newPatientData = {}
        if C.currentDICOMFile in C.storedDICOMSNames:
            dcm.read(path.join(DICOMS_DIR, C.currentDICOMFile))
            st.image(dcm.patientData.pixel_array)
            patientData = dcm.getPatientData()
            newPatientData = {}
        # with st.form(key="formEdit"):
            newPatientData["PatientName"] = st.text_input("Imie i nazwisko: ", value=str(patientData.PatientName)).replace(' ', '^')
            newPatientData["PatientID"] = st.text_input("Identyfikator pacjenta: ", value=str(patientData.PatientID))
            newPatientData["ImageComments"] = st.text_input("Komentarz do zdjęcia: ", value=str(patientData.ImageComments))
            # if st.form_submit_button("Zapisz zmiany"):
            #     print("insideif")
            #     dcm.edit(newPatientData)
            #     st.success("Poprawnie zapisano plik!")
elif C.currentApplication == C.APPS["CreateDICOM"]:
            
    newImg = None
    dcm = dicomIO()
    newPatientData = {}
    with st.form(key="formCreate"):
        dcm.filename = path.join(DICOMS_DIR, st.text_input("Nazwa pliku", value="nowyDICOM") + ".dcm")
        uploadedFile = st.file_uploader("Wgraj zdjęcie", type=["jpg"])
        if uploadedFile:
            with open(path.join(IMAGES_DIR, uploadedFile.name),"wb") as f: 
                f.write(uploadedFile.getbuffer())
            newImg = Image(path.join(IMAGES_DIR, uploadedFile.name))
            newImg = np.asarray(newImg.getImage())
        newPatientData["PatientName"] = st.text_input("Imie i nazwisko: ", value='')
        newPatientData["PatientID"] = st.text_input("Identyfikator pacjenta: ", value='')
        newPatientData["ImageComments"] = st.text_input("Komentarz do zdjęcia: ", value='')
        if st.form_submit_button(label="Utwórz plik"):
            print("inside if")
            dcm.write(newPatientData, newImg)
            st.success("Poprawnie dodano plik!")
