# -*- coding: utf-8 -*-
"""
Created on Wed Mar 24 19:16:24 2021

@author: SinghAs
"""

#assumes DeepMRSeg is installed 
from DeepMRSeg import deepmrseg_test

import SimpleITK as sitk
import sys as _sys
import os
  
print("wrapper called") # info for mitk debugging

# function to write input data_list as expected by DeepMRSeg
def csvwriter(fname, data_list):
	import csv
	with open(fname, 'w', newline='') as file:
		writer = csv.writer(file, delimiter=',')
		writer.writerows(data_list)
    
#pre-defined temp location to read/write
predefinedTempPath = 'C:/workspace/projects/DeepMRSegApp/Modules/CbicaDeepMRSeg/resources/temp/'

#save the incoming simple itk image to pre-defined location
inputFileSavePath = predefinedTempPath + 'inputFile.nii.gz'
writer = sitk.ImageFileWriter()
writer.SetFileName (inputFileSavePath )
writer.Execute ( in_image );
print("incoming simple itk image saved")

#deepmrseg specific stuff starts

#path where output from DeepMRSeg will be saved
outPath = predefinedTempPath + "../Out/test_1_label.nii.gz"

#create data list for 1st data--> this needs to happen dynamically
data_list = [["ID", "T1", "out"],
             ["test_1", inputFileSavePath, outPath]]

#path to save csv file
csvpath = predefinedTempPath + "\Testing_n10_FileList.txt"

#write csv file
csvwriter(csvpath,data_list)
print("csv saved")

#create args for passing to DeepMRSeg
_sys.argv = ["deeprmseg_test",
	      "--sList",
	      csvpath, #this is what we created above
	      "--idCol",
	      "ID",
	      "--refMod",
	      "T1",
	      "--outCol",
	      "out",
	      "--roi",
	      "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Lists\\SkullStripping_ROI_Indices.csv",
	      "--mdlDir",
	      "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Models\\bestmodels\\",
	      "--prep",
	      "--num_classes",
	      "2",
	      "--rescale",
	      "norm",
	      "--xy_width",
	      "256",
	      "--ressize",
	      "1",
	      "--reorient",
	      "LPS",
	      "--verb",
	      "--nJobs",
	      "1"]

#call DeepMRSeg
deepmrseg_test._main()

print("deepmrseg run")
#deepmrseg specific stuff ends here

#read the output image as simple itk image from pre-defined location
reader = sitk.ImageFileReader()
reader.SetFileName ( outPath )
out_image = reader.Execute()
print("result read as simple itk image")
