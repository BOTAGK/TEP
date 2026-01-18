#pragma once
#include "ProblemData.hpp"
#include "MyEvaluator.hpp"
#include <vector>
using namespace std;

namespace LcVRPContest {
	class MyEvaluator
	{
	public:
		static constexpr double Wrong_VAL = -1.0;

		MyEvaluator(const ProblemData& data);

		double Evaluate(const int* solution) const;
		double Evaluate(const vector<int>& solution) const;
		double Evaluate(const vector<int>* solution) const;

		int getSolutionSize() const { return data_.getNumCustomers(); };
		int getNumVehicles() const { return data_.getNumGroups(); };
	private:
		const ProblemData& data_;
		bool validState_;
		int numCustomers_;
		int numGroups_;
		
		void ValidateProblemData();
	};
}


