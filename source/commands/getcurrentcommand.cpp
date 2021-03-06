/*
 *  getcurrentcommand.cpp
 *  Mothur
 *
 *  Created by westcott on 3/16/11.
 *  Copyright 2011 Schloss Lab. All rights reserved.
 *
 */

#include "getcurrentcommand.h"

//**********************************************************************************************************************
vector<string> GetCurrentCommand::setParameters(){	
	try {
		CommandParameter pclear("clear", "String", "", "", "", "", "","",false,false); parameters.push_back(pclear);
		CommandParameter pseed("seed", "Number", "", "0", "", "", "","",false,false); parameters.push_back(pseed);
        CommandParameter pinputdir("inputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(pinputdir);
		CommandParameter poutputdir("outputdir", "String", "", "", "", "", "","",false,false); parameters.push_back(poutputdir);
		
		vector<string> myArray;
		for (int i = 0; i < parameters.size(); i++) {	myArray.push_back(parameters[i].name);		}
		return myArray;
	}
	catch(exception& e) {
		m->errorOut(e, "GetCurrentCommand", "setParameters");
		exit(1);
	}
}
//**********************************************************************************************************************
string GetCurrentCommand::getHelpString(){	
	try {
		string helpString = "";
		helpString += "The get.current command outputs the current files saved by mothur.\n";
		helpString += "The get.current command has one parameter: clear.\n";
		helpString += "The clear parameter is used to indicate which file types you would like to clear values for, multiple types can be separated by dashes.\n";
		helpString += "The get.current command should be in the following format: \n";
		helpString += "get.current() or get.current(clear=fasta-name-accnos)\n";
		return helpString;
	}
	catch(exception& e) {
		m->errorOut(e, "GetCurrentCommand", "getHelpString");
		exit(1);
	}
}
//**********************************************************************************************************************
GetCurrentCommand::GetCurrentCommand(){	
	try {
		abort = true; calledHelp = true;
		setParameters();
        vector<string> tempOutNames;
        outputTypes["summary"] = tempOutNames;
	}
	catch(exception& e) {
		m->errorOut(e, "GetCurrentCommand", "GetCurrentCommand");
		exit(1);
	}
}
//**********************************************************************************************************************
string GetCurrentCommand::getOutputPattern(string type) {
    try {
        string pattern = "";
        
        if (type == "summary") {  pattern = "[filename],current_files.summary"; }
        else { m->mothurOut("[ERROR]: No definition for type " + type + " output pattern.\n"); m->setControl_pressed(true);  }
        
        return pattern;
    }
    catch(exception& e) {
        m->errorOut(e, "GetCurrentCommand", "getOutputPattern");
        exit(1);
    }
}
//**********************************************************************************************************************
GetCurrentCommand::GetCurrentCommand(string option)  {
	try {
		abort = false; calledHelp = false;   
		
		//allow user to run help
		if(option == "help") { help(); abort = true; calledHelp = true; }
		else if(option == "citation") { citation(); abort = true; calledHelp = true;}
		
		else {
			vector<string> myArray = setParameters();
			
			OptionParser parser(option);
			map<string,string> parameters = parser.getParameters();
			
			ValidParameters validParameter;
			//check to make sure all parameters are valid for command
			for (map<string,string>::iterator it = parameters.begin(); it != parameters.end(); it++) { 
				if (!validParameter.isValidParameter(it->first, myArray, it->second)) {  abort = true;  }
			}
			
            vector<string> tempOutNames;
            outputTypes["summary"] = tempOutNames;
            
			clearTypes = validParameter.valid(parameters, "clear");
			if (clearTypes == "not found") { clearTypes = ""; }
			else { util.splitAtDash(clearTypes, types);	}
            
            //if the user changes the output directory command factory will send this info to us in the output parameter
            outputDir = validParameter.valid(parameters, "outputdir");		if (outputDir == "not found"){  outputDir = ""; }
		}
		
	}
	catch(exception& e) {
		m->errorOut(e, "GetCurrentCommand", "GetCurrentCommand");
		exit(1);
	}
}
//**********************************************************************************************************************

int GetCurrentCommand::execute(){
	try {
		
		if (abort) { if (calledHelp) { return 0; }  return 2;	}
        
		cFactory = CommandFactory::getInstance();
        
		//user wants to clear a type
		if (types.size() != 0) {
			for (int i = 0; i < types.size(); i++) {
				
				if (m->getControl_pressed()) { break; }
				
				//look for file types
				if (types[i] == "fasta") {
					current->setFastaFile("");
				}else if (types[i] == "qfile") {
					current->setQualFile("");
				}else if (types[i] == "phylip") {
					current->setPhylipFile("");
				}else if (types[i] == "column") {
					current->setColumnFile("");
				}else if (types[i] == "list") {
					current->setListFile("");
				}else if (types[i] == "rabund") {
					current->setRabundFile("");
				}else if (types[i] == "sabund") {
					current->setSabundFile("");
				}else if (types[i] == "name") {
					current->setNameFile("");
				}else if (types[i] == "group") {
					current->setGroupFile("");
				}else if (types[i] == "order") {
					current->setOrderFile("");
				}else if (types[i] == "ordergroup") {
					current->setOrderGroupFile("");
				}else if (types[i] == "tree") {
					current->setTreeFile("");
				}else if (types[i] == "shared") {
					current->setSharedFile("");
				}else if (types[i] == "relabund") {
					current->setRelAbundFile("");
				}else if (types[i] == "design") {
					current->setDesignFile("");
				}else if (types[i] == "sff") {
					current->setSFFFile("");
				}else if (types[i] == "oligos") {
					current->setOligosFile("");
				}else if (types[i] == "accnos") {
					current->setAccnosFile("");
				}else if (types[i] == "taxonomy") {
					current->setTaxonomyFile("");
                }else if (types[i] == "constaxonomy") {
                    current->setConsTaxonomyFile("");
                }else if (types[i] == "contigsreport") {
                    current->setContigsReportFile("");
				}else if (types[i] == "flow") {
					current->setFlowFile("");
                }else if (types[i] == "biom") {
					current->setBiomFile("");
                }else if (types[i] == "count") {
					current->setCountFile("");
                }else if (types[i] == "summary") {
					current->setSummaryFile("");
                }else if (types[i] == "file") {
                    current->setFileFile("");
				}else if (types[i] == "processors") {
					current->setProcessors("1");
				}else if (types[i] == "all") {
					current->clearCurrentFiles();
				}else {
					m->mothurOut("[ERROR]: mothur does not save a current file for " + types[i]); m->mothurOutEndLine();
				}
			}
		}
		
        unsigned long long ramUsed, total;
        ramUsed = util.getRAMUsed(); total = util.getTotalRAM();
        m->mothurOut("\nCurrent RAM usage: " + toString(ramUsed/(double)GIG) + " Gigabytes. Total Ram: " + toString(total/(double)GIG) + " Gigabytes.\n");
        
		if (current->hasCurrentFiles()) {
            map<string, string> variables;
            variables["[filename]"] = util.getFullPathName(outputDir);
            string filename = getOutputFileName("summary", variables);
            
			m->mothurOutEndLine(); m->mothurOut("Current files saved by mothur:"); m->mothurOutEndLine();
			current->printCurrentFiles(filename);
            outputNames.push_back(filename); outputTypes["summary"].push_back(filename);
		}
        
        string inputDir = current->getInputDir();
        if (inputDir != "") {
            m->mothurOutEndLine(); m->mothurOut("Current input directory saved by mothur: " + inputDir); m->mothurOutEndLine();
        }
        
        string outputDir = current->getOutputDir();
        if (outputDir != "") {
            m->mothurOutEndLine(); m->mothurOut("Current output directory saved by mothur: " + outputDir); m->mothurOutEndLine();
        }
        string defaultPath = current->getDefaultPath();
        if (defaultPath != "") {
            m->mothurOutEndLine(); m->mothurOut("Current default directory saved by mothur: " + defaultPath); m->mothurOutEndLine();
        }
        
        
        string temp = "."; temp += PATH_SEPARATOR;

        temp = util.getFullPathName(temp);
        m->mothurOutEndLine(); m->mothurOut("Current working directory: " + temp); m->mothurOutEndLine();
        
        if (current->hasCurrentFiles()) {
            m->mothurOutEndLine();
            m->mothurOut("Output File Names: "); m->mothurOutEndLine();
            for (int i = 0; i < outputNames.size(); i++) { m->mothurOut(outputNames[i]); m->mothurOutEndLine(); }
            m->mothurOutEndLine();
        }
        
        return 0;
        
	}
	
	catch(exception& e) {
		m->errorOut(e, "GetCurrentCommand", "execute");
		exit(1);
	}
}

//**********************************************************************************************************************



