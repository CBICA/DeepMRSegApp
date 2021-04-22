/**
contact: software@cbica.upenn.edu
Copyright (c) 2018 University of Pennsylvania. All rights reserved.
Use of this source code is governed by license located in license file: https://github.com/CBICA/DeepMRSegApp/blob/main/LICENSE
**/
#include "DeepMRSegMediator.h"

#include <mitkImageToItk.h>
#include <mitkITKImageImport.h>
#include "mitkLogMacros.h"

#include <QFile>
#include <QDir>
#include <QCoreApplication>

#include <usGetModuleContext.h>
#include <mitkIPythonService.h>
#include <usModuleContext.h>


DeepMRSegMediator::DeepMRSegMediator()
{
	// any setup required goes here
	pythonFilesDirPath = "C:/workspace/projects/DeepMRSegApp/Modules/CbicaDeepMRSeg/resources";

	//load python service
	us::ModuleContext* context = us::GetModuleContext();
	m_PythonServiceRef = context->GetServiceReference<mitk::IPythonService>();
	m_PythonService = dynamic_cast<mitk::IPythonService*> (context->GetService<mitk::IPythonService>(m_PythonServiceRef));
	mitk::IPythonService::ForceLoadModule();

	// Remove existing entries from path
    // This ensures only dirs we explicitly allow will be found
	m_PythonService->Execute("import sys", mitk::IPythonService::SINGLE_LINE_COMMAND);

	// Find our python files if we haven't already and allow python to access them
	if (!pythonFilesDirFound)
	{
		LocatePythonFileDir();
	}

	// Add to path first just in case.
	RegisterResourceDir(pythonFilesDirPath);

	// Set cwd in python as if it was run natively.
	bool success = ChangeWorkingDirectory(pythonFilesDirPath);
	MITK_INFO << " change working directory: " << success;

	//default ivars
	this->m_InputPtr_Flair = nullptr;
	this->m_InputPtr_T1 = nullptr;
}

void DeepMRSegMediator::SetT1Image(mitk::Image::Pointer T1ImagePtr)
{
	this->m_InputPtr_T1 = T1ImagePtr;
}

void DeepMRSegMediator::SetFlairImage(mitk::Image::Pointer FlImagePtr)
{
	this->m_InputPtr_Flair = FlImagePtr;
}

void DeepMRSegMediator::Update()
{
	// transfer input image to python
	if(this->m_InputPtr_T1 != nullptr)
		m_PythonService->CopyToPythonAsSimpleItkImage(this->m_InputPtr_T1, "in_image");

	if(this->m_InputPtr_Flair != nullptr)
		m_PythonService->CopyToPythonAsSimpleItkImage(this->m_InputPtr_Flair, "in_image_fl");

	//calling the python deepmrseg wrapper
	this->RunSampleScript();

	// clean up after running script (better way than deleting individual variables?)
	if (m_PythonService->DoesVariableExist("in_image"))
		m_PythonService->Execute("del in_image");

	if (m_PythonService->DoesVariableExist("in_image_fl"))
		m_PythonService->Execute("del in_image_fl");

	if (m_PythonService->DoesVariableExist("out_image"))
	{
		//get image back from python
		m_LastOutput = m_PythonService->CopySimpleItkImageFromPython("out_image");
	}
}

mitk::Image::Pointer DeepMRSegMediator::GetOutput()
{
	return this->m_LastOutput;
}


void DeepMRSegMediator::RegisterResourceDir(std::string resourceDirPath)
{
	// construct a vector to feed to Python's absolute search dirs
	std::vector< std::string > absolute_search_dirs = { resourceDirPath };

	// Python will now also look in these dirs for modules/packages.
	// This path will be *APPENDED* to the search path.
	// this function only takes a vector of std::strings.
	m_PythonService->AddAbsoluteSearchDirs(absolute_search_dirs);
}

void DeepMRSegMediator::RegisterPackageDir(std::string packageDirPath)
{
	// construct a vector to feed to Python's absolute search dirs
	std::vector< std::string > absolute_search_dirs = { packageDirPath };

	// Python will now also look in these dirs for modules/packages.
	// This path will be *APPENDED* to the search path.
	// this function only takes a vector of std::strings.
	m_PythonService->AddAbsoluteSearchDirs(absolute_search_dirs);
}

std::string DeepMRSegMediator::LocatePythonFileDir()
{
	// Build tree and install tree structure are different...
	// So we search in both the executable dir and one directory above.
	// We use the module name to help prevent resource mixups/conflicts.

	auto execDir = QCoreApplication::applicationDirPath();
	MITK_DEBUG << (QString("DEBUG: applicationDirPath == ") + execDir).toStdString();

	QString moduleResourceDir("/MitkDeepMRSegMediator/resources");
	QString installResourceDirPath(execDir + moduleResourceDir);
	QString buildResourceDirPath(execDir + "/.." + moduleResourceDir);

	// Find path to our python files
	if (QDir(installResourceDirPath).exists())
	{
		pythonFilesDirPath = installResourceDirPath.toStdString();
		pythonFilesDirFound = true;
	}
	else if (QDir(buildResourceDirPath).exists())
	{
		pythonFilesDirPath = buildResourceDirPath.toStdString();
		pythonFilesDirFound = true;
	}
	else // failure case
	{
		pythonFilesDirPath = "";
		pythonFilesDirFound = false;
	}

	// return the location found
	return pythonFilesDirPath;
}


// Utility functions
void DeepMRSegMediator::PassArgsToPython(std::vector<std::string> args)
{
	/* This function allows us to spoof args by modifying sys.argv in python.
	 * This allows us to basically emulate being run from the command line
	 * for use with scripts that are usually run like that.
	 * This means we can flexibly wrap any script with C++ parsing,
	 * or just use the python script's parsing.
	 * All we need to do ahead of time is construct the args vector.
	 */

	 // import sys to make sure we can access this. 
	 // No worries: this will not cause another sys import to fail.
	m_PythonService->Execute("import sys", mitk::IPythonService::SINGLE_LINE_COMMAND);

	// insert executable name
	args.insert(args.begin(), QCoreApplication::applicationFilePath().toStdString());
	// read in all args
	for (int i = 0; i < args.size(); i++)
	{
		auto numString = QString::number(i).toStdString();
		m_PythonService->Execute("sys.argv[" + numString + "] = " + args[i],
			mitk::IPythonService::SINGLE_LINE_COMMAND);
	}

}

bool DeepMRSegMediator::ChangeWorkingDirectory(
	std::string newWorkingDirectoryPath)
{
	// This function allows us to set the working directory in Python to whatever we want.

	bool isOk = true; // assume success unless an error arises
	// import os to make sure we can access this. 
	// No worries: this will not cause another os import to fail.
	m_PythonService->Execute("import os", mitk::IPythonService::SINGLE_LINE_COMMAND);
	// Mind the escaped quotes. These are necessary.
	m_PythonService->Execute("os.chdir(\"" + newWorkingDirectoryPath + "\")",
		mitk::IPythonService::SINGLE_LINE_COMMAND);
	if (m_PythonService->PythonErrorOccured())
	{
		isOk = false;
	}
	return isOk;
}

bool DeepMRSegMediator::IsOkayToRun()
{
	bool ok = true; // Assumed ok unless below conditions fail

	// Check if python files were found
	if (!pythonFilesDirFound)
	{
		MITK_ERROR << "Required python files were not found for this module."
			"Check permissions or reinstall if this problem persists.";
		ok = false;
	}
	// Add more failure conditions here as necessary, especially if more setup is required

	// return final status
	return ok;

}


void DeepMRSegMediator::RunSampleScript()
{
	MITK_INFO << "  DeepMRSegMediator::RunSampleScript() ";
	// With everything else set up, the logic for running the script goes here.
	auto entryPointFilename = "deepmrsegwrapper.py"; //"deepmrseg_test.py";
	
	std::string fullfilepath = pythonFilesDirPath + "/" + entryPointFilename;

	MITK_INFO << "full file path: " << fullfilepath;

	// Execute our entrypoint. Any last-second setup or checks should be done before this.
	m_PythonService->ExecuteScript(fullfilepath);

}


