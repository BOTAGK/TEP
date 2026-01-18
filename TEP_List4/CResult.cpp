#include "CResult.h"
#include "CError.h"
#include "CTree.h"

template<>
CResult<CTree*, CError> CResult<CTree*, CError>::cFail(CError* pcError) {
	CTree* newTree = new CTree();

	return CResult<CTree*, CError>(newTree);
 }

template<>
CResult<CTree*, CError> CResult<CTree*, CError>::cFail(const vector<CError*>& vErrors) {
	CTree* newTree = new CTree();
	return CResult<CTree*, CError>(newTree);
}
