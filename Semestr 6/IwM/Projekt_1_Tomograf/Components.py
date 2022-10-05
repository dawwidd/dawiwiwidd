import streamlit as st
from config import *
from os import listdir, path
from CTScanner import *
from PIL import Image as img
from Image import *
from dicomIO import dicomIO
from matplotlib import pyplot as plotResult
import plotly.express as px
from plotly.subplots import make_subplots

class Components:
    APPS = {"CT":"Symulacja tomografu", "DICOM": "Przeglądarka DICOM", "CreateDICOM": "Utwórz DICOM"}
    def __init__(self):
        self.storedImagesNames = listdir(IMAGES_DIR)
        self.storedDICOMSNames = listdir(DICOMS_DIR)
        self.currentFile = ''
        self.currentDICOMFile = ''
        self.scanned = {}
        self.session = st.session_state
        self.step = 1
        self.deviceCount = 100
        self.currentApplication = self.APPS["CT"]
        self.deviceRange = 180
        self.scanCount = int(180//self.step)
        self.upToAngle = 180

    def sidebar(self):
        st.sidebar.title("IwM")
        self.currentApplication = st.sidebar.selectbox("Wybierz aplikację", (self.APPS["CT"], self.APPS["DICOM"], self.APPS["CreateDICOM"]))
    
    def fileUploader(self, directory):
        file = st.file_uploader(f"Wgraj plik {directory[:-2]}")
        if file is not None:
            with open(path.join(directory,file.name),"wb") as f: 
                f.write(file.getbuffer())  
                self.reloadFiles(directory)   
                st.success("Saved File")
                
    def reloadFiles(self, directory):
        self.storedImagesNames = listdir(directory)

    def fileSelector(self, directory):
        if directory == IMAGES_DIR:
            self.currentFile = st.selectbox("Wybierz zdjęcie", [''] + self.storedImagesNames)
        elif directory == DICOMS_DIR:
            self.currentDICOMFile = st.selectbox("Wybierz DICOM",  [''] + self.storedDICOMSNames)
            
    def settings(self):
        with st.form(key="image_set"):
            self.step = st.slider('Krok [°]', min_value=0.1, max_value=10.0, value=float(self.step), step=0.1)
            self.deviceCount = st.slider('Liczba urządzeń', min_value=10, max_value=360, value=self.deviceCount)
            self.deviceRange = st.slider('Rozpiętość urządzeń', min_value=10, max_value=180, value=self.deviceRange)
            self.upToAngle = st.slider('Licz, aż do kąta: ', min_value=0, max_value=180, value=self.upToAngle)
            self.scanCount = int(180//self.step)
            submit = st.form_submit_button(label="Zatwierdź")
        if submit:
            self.run()
    
    def imagePreview(self):
        if self.currentFile in self.scanned.keys():
            st.image(img.fromarray(self.scanned[self.currentFile].getImage() * 255).convert('L'), width=None)
            st.image(img.fromarray(self.scanned[self.currentFile].getTransposedSinogram() * 255).convert('L'), width=None)
            st.image(img.fromarray(self.scanned[self.currentFile].getResultImage() * 255).convert('L'), width=None)

        elif self.currentFile != '':
            st.error(f'Plik: {self.currentFile} nie został jeszcze przetworzony. Sprawdź ustawienia i wciśnij [Generuj]')
    
    def getCurrentFile(self):
        return path.join(IMAGES_DIR, self.currentFile)
    
    @st.cache(suppress_st_warning=True)
    def run(self):
        image = Image(self.getCurrentFile())
        self.scanned[self.currentFile] = CTScanner(
            image.centerWithPadding,
            image.sizeWithPadding//2,
            self.deviceRange,
            self.deviceCount,
            self.scanCount,
            image.getImageWithPadding(),
            self.upToAngle
        )
        self.scanned[self.currentFile].calcSinogramData()
        self.scanned[self.currentFile].calcResultData()
                
    def header(self):
        st.header("Symulacja tomografu komputerowego")
    
    def horizontalSeparator(self):
        st.markdown("---")
        
    def headerCT(self):
        st.subheader("Symulator")

    def headerDICOM(self):
        st.subheader("DICOM")

    # def loadDICOM(self):
    #     colL, _, colR = st.columns([1,3,1])
    #     if colL.button('Wczytaj') and self.currentDICOMFile != '':
    #         if self.currentDICOMFile in self.storedDICOMSNames:
    #             dcm = dicomIO()
    #             dcm.read(path.join(DICOMS_DIR, self.currentDICOMFile))
    #             st.image(dcm.patientData.pixel_array)
    #             self.editDICOM(dcm)
    #     if colR.button('Utwórz nowy'):
    #         # self.createDICOM()
    #         with st.form(key="form"):
    #             x = st.time_input("Input:")
    #             if st.form_submit_button("submit"):
    #                 st.warning(x)
    #                 print("inside form form if after buton")
    
    # def editDICOM(self, dcm):
    #     patientData = dcm.getPatientData()
    #     newPatientData = {}
    #     with st.form(key="dicom_data_edit"):
    #         newPatientData["PatientName"] = st.text_input("Imie i nazwisko: ", value=str(patientData.PatientName)).replace(' ', '^')
    #         newPatientData["PatientID"] = st.text_input("Identyfikator pacjenta: ", value=str(patientData.PatientID))
    #         newPatientData["ImageComments"] = st.text_input("Komentarz do zdjęcia: ", value=str(patientData.ImageComments))
    #         if st.form_submit_button("Zapisz zmiany"):
    #             print("inside if")
    #             dcm.edit(newPatientData)
    #             st.success("Poprawnie zapisano plik!")
            
    # def createDICOM(self):
    #     # dcm = dicomIO()
    #     newPatientData = {}
    #     with st.form(key="form"):
    #         st.text_input("wpisz cos")
    #         # dcm.filename = path.join(DICOMS_DIR, st.text_input("Nazwa pliku", value="nowyDICOM") + ".dcm")
    #         # newImg = st.file_uploader("Wgraj zdjęcie", type=["jpg"])
    #         # newPatientData["PatientName"] = st.text_input("Imie i nazwisko: ", value='')
    #         # newPatientData["PatientID"] = st.text_input("Identyfikator pacjenta: ", value='')
    #         # newPatientData["ImageComments"] = st.text_input("Komentarz do zdjęcia: ", value='')
            
    #         if st.form_submit_button(label="Utwórz plik"):
    #             # dcm.write(newPatientData, newImg)
    #             # f = open("plik.XDKURWA", "w")
    #             # f.write("Now the file has more content!")
    #             # f.close()
    #             st.success("Poprawnie dodano plik!")