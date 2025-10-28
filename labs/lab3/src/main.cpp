#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <omp.h>

#include "../include/Constants.h"

void generateVector(std::vector<int> &);
void calculateProductParallelNoFor(std::vector<int>, std::vector<int>);

int main() {
    std::ofstream time_long(Constants::folder + "time-long.dat");

    for (int i = 0; i < (int)Constants::longOfVector.size(); i++) {
        std::vector<int> vectorA(Constants::longOfVector[i]);
        std::vector<int> vectorB(Constants::longOfVector[i]);

        generateVector(vectorA);
        generateVector(vectorB);

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        calculateProductParallelNoFor(vectorA, vectorB);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<long double, std::milli> milli_diff = end - start;
        long double time_taken1 = milli_diff.count();

        start = std::chrono::high_resolution_clock::now();
        calculateProductParallelNoFor(vectorA, vectorB);
        end = std::chrono::high_resolution_clock::now();
        milli_diff = end - start;
        long double time_taken1 = milli_diff.count();

        time_long << Constants::longOfVector[i] << " " << time_taken1 << " " << time_taken2 << std::endl;
    }

    time_long.close();

    return 0;
}

void generateVector(std::vector<int> &vector) {
    std::random_device rnd_device;
    std::mt19937 mersenne_engine {rnd_device()};
    std::uniform_int_distribution<int> dist {Constants::minNumberOfVector, Constants::maxNumberOfVector};

    auto gen = [&]() {
        return dist(mersenne_engine);
    };

    std::generate(vector.begin(), vector.end(), gen);
}

void calculateProductParallelNoFor(std::vector<int> firstVector, std::vector<int> secondVector) {
    int total_scalar_product = 0;
   	 
	#pragma omp parallel num_threads(Constants::numberOfThreads)
	{
		int thread_id = omp_get_thread_num();
		int num_threads = omp_get_num_threads();

		int start = thread_id * (firstVector.size() / num_threads);
			
		int end;
		if (thread_id == num_threads - 1)
			end = firstVector.size();
		else
			end = (thread_id + 1) * (firstVector.size() / num_threads);
			
		int partial_result = 0;
		for (int i = start; i < end; i++)
			partial_result += firstVector[i] * secondVector[i];

		#pragma omp critical
        total_scalar_product += partial_results[i];
	}
}
