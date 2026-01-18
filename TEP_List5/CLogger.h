#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class CTree;

class CLogger
{
public:
	static const string S_LOG_FILE_NAME;

	static void vLogSuccess();

	static void vLogSave(CTree* const& pcTree);

	template <typename T>
	static void vLogSave(const T& val);

	template <typename E>
	static void vLogFailure(const vector<E*>& vErrors);

};

template<typename T>
void CLogger::vLogSave(const T& val) {}

template<typename E>
void CLogger::vLogFailure(const vector<E*>& vErrors) {
	ofstream fFile;

	fFile.open(S_LOG_FILE_NAME.c_str(), ios::app);
	if (fFile.is_open()) {
		fFile << "[RESULT] Operation Failed. Errors: " << endl;

		for (size_t i = 0; i < vErrors.size(); i++) {
			if (vErrors[i] != NULL) {
				fFile << " - " << vErrors[i]->getMessage() << endl;
			}
		}
		fFile << "------------------------------------" << endl;
		fFile.close();
	}
}

