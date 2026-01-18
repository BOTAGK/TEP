#include "Individual.hpp"
#include <random>
#include "GeneticAlgorithm.hpp"
#include <iostream>
using namespace std;
using namespace LcVRPContest;

Individual::Individual(int numberOfClients, int numberOfGroups)
	: fitness_(-1.0)
{
	genotype_.resize(numberOfClients);

	uniform_int_distribution<> distrib(0, numberOfGroups - 1);

	for (int i = 0; i < numberOfClients; i++) {
		genotype_[i] = distrib(GeneticAlgorithm::gen_);
	}
}

Individual::Individual(const Individual& other)
	: fitness_(other.fitness_),
	  genotype_(other.genotype_){}

Individual::Individual(vector<int>&& genotype)
	: fitness_(-1.0),
	  genotype_(move(genotype)){}

double Individual::getFitness() const {
	return fitness_;
}

double Individual::calculateFitness(const LcVRPContest::MyEvaluator& evaluator){
	if (!this->isEvaluated()) {
		fitness_ = evaluator.Evaluate(genotype_);
	}
	
	return fitness_;
} 

void Individual::setFitness(double fitness) {
	fitness_ = fitness;
}

void Individual::mutate(double multProb, int numberOfGroups){

	uniform_real_distribution<> probDist(0.0, 1.0);
	uniform_int_distribution<> groupDist(0, numberOfGroups - 1);

	for (size_t i = 0; i < genotype_.size(); i++) {
		if (probDist(GeneticAlgorithm::gen_) < multProb) {
			genotype_[i] = groupDist(GeneticAlgorithm::gen_);
		}
	}
}

pair<Individual, Individual> Individual::crossover(const Individual& secondParent) const{
	uniform_int_distribution<> parentDist(1, static_cast<int>(genotype_.size()) - 1);
	int cutPoint = parentDist(GeneticAlgorithm::gen_);

	auto myStart = genotype_.begin();
	auto myCut = genotype_.begin() + cutPoint;
	auto myEnd = genotype_.end();

	auto otherStart = secondParent.genotype_.begin();
	auto otherCut = secondParent.genotype_.begin() + cutPoint;
	auto otherEnd = secondParent.genotype_.end();

	vector<int> childGen1(myStart, myCut);
	childGen1.insert(childGen1.end(), otherCut, otherEnd);

	vector<int> childGen2(otherStart, otherCut);
	childGen2.insert(childGen2.end(), myCut, myEnd);

	return make_pair(
		Individual(move(childGen1)),
		Individual(move(childGen2))
	);
}

bool Individual::operator<(const Individual& other) const{
	return fitness_ < other.fitness_;
}

void Individual::printGenotype() const{
	cout << "Genotyp : [ ";
	for (const auto& gene : genotype_) {
		cout << gene << ", ";
	}
	cout << " ] " << endl;
}

void Individual::printFitness() const{
	cout << "Fitness: " << getFitness() << endl;
}



