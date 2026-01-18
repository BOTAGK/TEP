#include "CLogger.h"
#include "CTree.h"

const string CLogger::S_LOG_FILE_NAME = "result_log.txt";

void CLogger::vLogSave(CTree* const& pcTree) {
	if (pcTree != NULL) {
		ofstream fFile;
		fFile.open(S_LOG_FILE_NAME.c_str(), ios::app);

		if (fFile.is_open()) {
			fFile << "[SUCCESS TREE SAVE] -------------------" << endl;
			fFile << pcTree->treeToString() << endl;
			fFile << "---------------------------------------" << endl;
			fFile.close();
		}
	}
}

void CLogger::vLogSuccess() {
	ofstream fFile;

	fFile.open(S_LOG_FILE_NAME.c_str(), ios::app);
	if (fFile.is_open()) {
		fFile << "[RESULT] Operation Succesful" << endl;
		fFile.close();
	}
}