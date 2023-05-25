cmake_minimum_required(VERSION 3.21)
project(genetic_flowshop_new)

set(CMAKE_CXX_STANDARD 14)

add_executable(genetic_flowshop_new main.cpp RandomNumberGenerator.h instance.h Chromosome.h GeneticAlgorithm.h Population.h FlowShop.h)
