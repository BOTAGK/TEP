#include "GeneticAlgorithm.hpp"
#include <iostream>

using namespace LcVRPContest;

// MODYFIKACJA
//do algorytmu genetycznego dodac metoda krzyzowania 3 rodzicow tabela 11 12 13 21 22 23 31 32 33
// zwroci wszystkich dzieci bez kopii rodzicow
// 
// Drzewo genealogiczne wskazniki na rodzicow individuali
//
// PYTANIA OGOLNE:
// kara za wrocenie do depotu to czesc optymalizatora 
// 
// napisanie calego problem Loadera problem data 
//
// Optymalizator tylko zna evaluator a nie jest jego wlascicielem

//Pytania: Czy mozemy tak jak w paczce konkursowej do zoptymalizowania wydajnosci robic gettery i settery w hpp?

mt19937 GeneticAlgorithm::gen_(random_device{}());



GeneticAlgorithm::GeneticAlgorithm(const MyEvaluator& evaluator, const GAParams& params)
	: evaluator_(evaluator),
	params_(params),
	bestSolution_(Individual(evaluator.getSolutionSize(), evaluator.getNumVehicles()))
{
	bestSolution_.setFitness(numeric_limits<double>::max());

	population_.reserve(params_.populationSize);
	nextGeneration_.reserve(params_.populationSize);
}

void GeneticAlgorithm::run(int maxIterations) {
	initializePopulation();
	evaluatePopulation(population_);
	updateBestSolution();

	int generation = 0;
	
	while (generation < maxIterations) {
		nextGeneration_.clear();
		//elitaryzm
		nextGeneration_.push_back(bestSolution_);

		crossPopulation();
		mutatePopulation();

		population_ = move(nextGeneration_);
		evaluatePopulation(population_);
		updateBestSolution();
		bestSolution_.printGenotype();
		bestSolution_.printFitness();
		generation++;
	}
}

void GeneticAlgorithm::initializePopulation() {
	population_.clear();
	population_.reserve(params_.populationSize);

	int clients = evaluator_.getSolutionSize();
	int vehicles = evaluator_.getNumVehicles();

	for (int i = 0; i < params_.populationSize; i++) {
		population_.emplace_back(clients, vehicles);
	}
}


//dodanie dist i parentDist czytelnosc klasy wzgledem niewielkiego spadku wydajnosci
void GeneticAlgorithm::crossPopulation() {
	nextGeneration_.reserve(population_.size() + 2);

	if (population_.size() == 0) {
		cout << "blad populacja zerowa" << endl;
		return;
	}

	uniform_real_distribution<double> dist(0.0, 1.0);
	int tournamentSize = 3;

	while (nextGeneration_.size() < (size_t)params_.populationSize) {
		//losujemy parentow jesli crossover zajdzie tworzymy dzieci dodajemy do nextGen,jesli nie przepisujemy rodzicow
		const Individual& parent1 = population_[doTournament(3)];
		const Individual& parent2 = population_[doTournament(3)];

		auto children = (dist(gen_) < params_.crossoverRate)
			? parent1.crossover(parent2)
			: make_pair(parent1, parent2);

		nextGeneration_.push_back(move(children.first));
		nextGeneration_.push_back(move(children.second));
	}

	//jesli dodalismy 101 elementow a jest 100 miejsca usuwamy ostatni
	while (nextGeneration_.size() > (size_t)params_.populationSize) {
		nextGeneration_.pop_back();
	}
}

void GeneticAlgorithm::mutatePopulation() {
	for (size_t i = 0; i < nextGeneration_.size(); i++) {
		nextGeneration_[i].mutate(params_.mutationRate, evaluator_.getNumVehicles());
	}
}

void GeneticAlgorithm::evaluatePopulation(vector<Individual>& population) {
	for (int i = 0; i < population.size(); i++) {
		population[i].calculateFitness(evaluator_);
	}
}

void GeneticAlgorithm::updateBestSolution() {
	double bestFit = bestSolution_.getFitness();

	for (const auto& ind : population_) {
		double currentFit = ind.getFitness();

		if (currentFit != MyEvaluator::Wrong_VAL && currentFit < bestFit) {
			bestSolution_ = ind;
			bestFit = currentFit;
		}
	}
}

const vector<int>& GeneticAlgorithm::getBestSolution() const {
	return bestSolution_.getGenotype();
}

double GeneticAlgorithm::getBestFitness() const {
	return bestSolution_.getFitness();
}

int GeneticAlgorithm::doTournament(int k) {
	uniform_int_distribution<int> dist(0, (int)population_.size() - 1);
	int bestIdx = dist(gen_);
	double bestFitness = population_[bestIdx].getFitness();

	for (int i = 1; i < k; i++) {
		int challangedIdx = dist(gen_);
		double challangedFitness = population_[challangedIdx].getFitness();

		if (challangedFitness < bestFitness) {
			bestIdx = challangedIdx;
			bestFitness = challangedFitness;
		}
	}

	return bestIdx;
}


