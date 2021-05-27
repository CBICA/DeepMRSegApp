# -*- coding: utf-8 -*-
"""
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file: https://github.com/CBICA/DeepMRSegApp/blob/main/LICENSE
Created on Wed Mar 24 19:16:24 2021
@author: Ashish Singh
"""

#assumes DeepMRSeg is installed 
from DeepMRSeg import deepmrseg_test, utils

import SimpleITK as sitk
import sys as _sys
import os as _os
import nibabel
import sitk2nibabel
  
print("wrapper called") # info for mitk debugging
_sys.stdout.flush()

# function to write input data_list as expected by DeepMRSeg
def csvwriter(fname, data_list):
	import csv
	with open(fname, 'w', newline='') as file:
		writer = csv.writer(file, delimiter=',')
		writer.writerows(data_list)
    
#pre-defined temp location to read/write
predefinedTempPath = 'C:/workspace/projects/DeepMRSegApp/Modules/CbicaDeepMRSeg/resources/temp/'

mdlPath = "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Models\\bestmodels\\"
allmodels = []
#for mDir in mdlPath:
for checkpoint in _os.listdir( mdlPath ):
    cppath = _os.path.join( mdlPath + '\\' + checkpoint )
    print('cppath',cppath)
    deepmrseg_test.load_model( allmodels,cppath )

#csv prep
roi_indices = utils.get_roi_indices( "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Lists\\SkullStripping_ROI_Indices.csv" )
 
#_sys.exit(0)
#convert sitk to nibabel image
nibObj = sitk2nibabel.SimpleITKAsNibabel(in_image)
print('nibObj',nibObj)

#convert sitk2nibabel class type to nibabel.Nifti1Image
print('changing nibObj class type')
nibObj.__class__ = nibabel.Nifti1Image
print('nibObj',nibObj)

#save the incoming simple itk image to pre-defined location
#inputFileSavePath = predefinedTempPath + 'inputFile.nii.gz'
#writer = sitk.ImageFileWriter()
#writer.SetFileName (inputFileSavePath )
#writer.Execute ( in_image );
#print("incoming simple itk image saved")

#deepmrseg specific stuff starts

#path where output from DeepMRSeg will be saved
outPath = predefinedTempPath + "../Out/test_1_label.nii.gz"

#create data list for 1st data--> this needs to happen dynamically
#data_list = [["ID", "T1", "out"],
#             ["test_1", inputFileSavePath, outPath]]

##path to save csv file
#csvpath = predefinedTempPath + "\Testing_n10_FileList.txt"

##write csv file
#csvwriter(csvpath,data_list)
#print("csv saved")

##create args for passing to DeepMRSeg
#_sys.argv = ["deeprmseg_test",
#	      "--sList",
#	      csvpath, #this is what we created above
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

#call DeepMRSeg
#deepmrseg_test._main()

print('calling predict_classes')
#call predecitClasses
resultnibobj = deepmrseg_test.predict_classes( refImg=nibObj,
    otherImg=[],
    num_classes=2,
    allmodels=allmodels,          ### This is loaded in main()
    roi_indices=roi_indices,       ### Path to csv
    out=None,
    probs=False,
    rescalemethod='batch',
    ressize=float(1),
    orient='LPS',
    xy_width=256,
    batch_size=64,
    nJobs=1 )


print("deepmrseg run")
#deepmrseg specific stuff ends here

#read the output image as simple itk image from pre-defined location
#reader = sitk.ImageFileReader()
#reader.SetFileName ( outPath )
#out_image = reader.Execute()
#print("result read as simple itk image")

#resultnibobj.to_filename( outPath )
#print("nibabel result saved")

# print('in_image')
# print(in_image)
# print(in_image.GetPixelIDTypeAsString())

# print('creating out_image object')
# out_image = sitk.GetImageFromArray( resultnibobj.get_fdata().transpose() )
# out_image.CopyInformation(in_image)
# print(out_image.GetPixelIDTypeAsString())

# print('Setting metadata')
# for k in in_image.GetMetaDataKeys():
	# out_image.SetMetaData( k,in_image.GetMetaData(k) )
	# print(k,in_image.GetMetaData(k),out_image.GetMetaData(k))

# print('setting datatype')
# out_image.SetMetaData('datatype',sitk.sitkUInt8)

# print('out_image')
# print(out_image)

# print('writing sitk out_image')
# sitk.WriteImage( out_image, outPath )

out_image = nibabel2sitk(in_image,resultnibobj)

