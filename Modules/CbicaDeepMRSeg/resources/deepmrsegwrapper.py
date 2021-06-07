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

# function to convert nibabel image produced by DeepMRSeg to simpleitk image
def nibabel2sitk(refimg,nibimg):
	sitkimage = sitk.GetImageFromArray(nibimg.get_data().transpose())
	sitkimage.CopyInformation(refimg)
	print(sitkimage.GetPixelIDTypeAsString())

	#cast to same type as refimage
	sitkimage = sitk.Cast(sitkimage, refimg.GetPixelID())

	print('Setting metadata')
	for k in refimg.GetMetaDataKeys():
		sitkimage.SetMetaData( k,refimg.GetMetaData(k) )
		
	return sitkimage

mdlPath = "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Models\\bestmodels\\"
allmodels = []
#for mDir in mdlPath:
for checkpoint in _os.listdir( mdlPath ):
    cppath = _os.path.join( mdlPath + '\\' + checkpoint )
    print('cppath',cppath)
    deepmrseg_test.load_model( allmodels,cppath )

#csv prep
roi_indices = utils.get_roi_indices( "C:\\workspace\\projects\\DeepMRSegApp\\Modules\\CbicaDeepMRSeg\\resources\\Lists\\SkullStripping_ROI_Indices.csv" )
 
#convert sitk to nibabel image
nibObj = sitk2nibabel.SimpleITKAsNibabel(in_image)
print('nibObj',nibObj)

#convert sitk2nibabel class type to nibabel.Nifti1Image
nibObj.__class__ = nibabel.Nifti1Image

#deepmrseg specific stuff starts

#call predict_classes - the real workhorse
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

#convert result back to sitk
out_image = nibabel2sitk(in_image,resultnibobj)

