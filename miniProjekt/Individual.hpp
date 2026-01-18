#pragma once
#include "MyEvaluator.hpp"
#include <random>
#include <vector>
using namespace std;
namespace LcVRPContest {
	class Individual{
	public:

		Individual(int numberOfClients, int numberOfGroups);
		Individual(const Individual& other);

		void mutate(double multProb, int numberOfGroups);
		pair<Individual, Individual> crossover(const Individual& secondParent) const;

		double getFitness() const;
		void setFitness(double fitness);
		double calculateFitness(const LcVRPContest::MyEvaluator& evaluator);

		const vector<int>& getGenotype() const { return genotype_; };

		bool operator<(const Individual& other) const;
		void printGenotype() const;
		void printFitness() const;

	private:
		vector<int> genotype_;
		double fitness_;

		Individual(vector<int>&& genotype);

		
		bool isEvaluated() const { return fitness_ != -1; };
		
	};
}
