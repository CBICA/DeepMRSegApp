# -*- coding: utf-8 -*-
"""
Created on Wed Mar 24 19:16:24 2021

@author: SinghAs
"""

from DeepMRSeg import deepmrseg_test
import SimpleITK as sitk
import sys as _sys
import os
  
#if len ( sys.argv ) < 3:
#    print( "Usage: Image Intensity Invert <input> <output>" )
#    sys.exit ( 1 )
  
# reader = sitk.ImageFileReader()
# reader.SetFileName ( sys.argv[1] )
# image = reader.Execute()

# inverter = sitk.InvertIntensityImageFilter()
# output = inverter.Execute(image)
  
# writer = sitk.ImageFileWriter()
# writer.SetFileName ( sys.argv[2] )
# writer.Execute ( output );
print("wrapper called")
def csvwriter(fname, data_list):
	import csv
	with open(fname, 'w', newline='') as file:
		writer = csv.writer(file, delimiter=',')
		writer.writerows(data_list)
    
#define a temp location to read/write
predefinedTempPath = 'C:/workspace/projects/DeepMRSegApp/Modules/CbicaDeepMRSeg/resources/temp/'

#save the incoming simple itk image to a pre-defined location
inputFileSavePath = predefinedTempPath + 'inputFile.nii.gz'
writer = sitk.ImageFileWriter()
writer.SetFileName (inputFileSavePath )
writer.Execute ( in_image );
print("incoming simple itk image saved")

#deepmrseg specific stuff
#_sys.argv = ["deeprmseg_test",
#	      "--sList",
#	      "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Lists\\Testing_n10_FileList.txt",
#	      "--idCol",
#	      "ID",
#	      "--refMod",
#	      "T1",
#	      "--outCol",
#	      "out",
#	      "--roi",
#	      "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Lists\\SkullStripping_ROI_Indices.csv",
#	      "--mdlDir",
#	      "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Models\\bestmodels\\",
#	      "--prep",
#	      "--num_classes",
#	      "2",
#	      "--rescale",
#	      "norm",
#	      "--xy_width",
#	      "256",
#	      "--ressize",
#	      "1",
#	      "--reorient",
#	      "LPS",
#	      "--verb",
#	      "--nJobs",
#	      "1"]

outPath = predefinedTempPath + "../Out/test_1_label.nii.gz"
data_list = [["ID", "T1", "out"],
             ["test_1", inputFileSavePath, outPath]]

csvpath = predefinedTempPath + "\Testing_n10_FileList.txt"

csvwriter(csvpath,data_list)
print("csv saved")

_sys.argv = ["deeprmseg_test",
	      "--sList",
	      csvpath,
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

deepmrseg_test._main()

print("deepmrseg run")

#read the output image as simple itk image from pre-defined location
reader = sitk.ImageFileReader()
#outputPath = predefinedTempPath + 'test_1_label.nii.gz'
reader.SetFileName ( outPath )
out_image = reader.Execute()
print("result read as simple itk image")
#
#inverter = sitk.InvertIntensityImageFilter()
#out_image = inverter.Execute(in_image)
