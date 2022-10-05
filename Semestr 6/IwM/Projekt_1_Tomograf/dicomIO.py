from os import path
from pydicom import dcmread
from pydicom.dataset import Dataset, FileDataset
from pydicom.uid import ExplicitVRLittleEndian
import pydicom._storage_sopclass_uids

from skimage.util import img_as_ubyte
from skimage.exposure import rescale_intensity

class dicomIO:
    def __init__(self):
        self.filename = None
        self.patientData = None

    def read(self, filename):
        if path.exists(filename):
            self.filename = filename
            self.patientData = dcmread(filename)
        else:
            raise IOError(f"Nie ma takiego pliku: {filename}!")
    
    def getPatientData(self):
        if self.patientData:
            return self.patientData
        else:
            raise IOError("Brak danych. Nie wczytano pliku!")
    
    def edit(self, newPatientData):
        if not self.patientData:
            raise ValueError("Brak danych dicom do edycji!")
        
        if newPatientData:
            # img_converted = img_as_ubyte(rescale_intensity(img, out_range=(0.0, 1.0)))
            self.patientData.PatientName = newPatientData["PatientName"]
            self.patientData.PatientID = newPatientData["PatientID"]
            self.patientData.ImageComments = newPatientData["ImageComments"]    

        # if newImg:
        #     img_converted = img_as_ubyte(rescale_intensity(newImg, out_range=(0.0, 1.0)))
        #     self.patientData.PixelData = img_converted.tobytes()
        print("zapisywanie...")
        self.patientData.save_as(self.filename, write_like_original=False)
    
    def write(self, patient_data, img):
        img_converted = img_as_ubyte(rescale_intensity( img, out_range=(0.0, 1.0)))
        
        meta = Dataset()
        meta.MediaStorageSOPClassUID = pydicom._storage_sopclass_uids.CTImageStorage
        meta.MediaStorageSOPInstanceUID = pydicom.uid.generate_uid()
        meta.TransferSyntaxUID = pydicom.uid.ExplicitVRLittleEndian  

        ds = FileDataset(None, {}, preamble=b"\0" * 128)
        ds.file_meta = meta

        ds.is_little_endian = True
        ds.is_implicit_VR = False

        ds.SOPClassUID = pydicom._storage_sopclass_uids.CTImageStorage
        ds.SOPInstanceUID = meta.MediaStorageSOPInstanceUID
        
        ds.PatientName = patient_data["PatientName"]
        ds.PatientID = patient_data["PatientID"]
        ds.ImageComments = patient_data["ImageComments"]

        ds.Modality = "CT"
        ds.SeriesInstanceUID = pydicom.uid.generate_uid()
        ds.StudyInstanceUID = pydicom.uid.generate_uid()
        ds.FrameOfReferenceUID = pydicom.uid.generate_uid()

        ds.BitsStored = 8
        ds.BitsAllocated = 8
        ds.SamplesPerPixel = 1
        ds.HighBit = 7

        ds.ImagesInAcquisition = 1
        ds.InstanceNumber = 1

        ds.Rows, ds.Columns = img_converted.shape

        ds.ImageType = r"ORIGINAL\PRIMARY\AXIAL"

        ds.PhotometricInterpretation = "MONOCHROME2"
        ds.PixelRepresentation = 0

        pydicom.dataset.validate_file_meta(ds.file_meta, enforce_standard=True)

        ds.PixelData = img_converted.tobytes()

        ds.save_as(self.filename, write_like_original=False)
    

    