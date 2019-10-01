#pragma once
//algorithms with graph using function with edges
//do not use other and this file altogether
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <random>

namespace my {
	template <class T>
	class Graph {
	public:
		virtual bool AddElement(T) = 0;
		virtual bool EraseElement(T) = 0
			virtual bool CheckConnectivility() = 0;
		virtual int FindElement(T) = 0;
		virtual bool BFS(T, T, T, bool) = 0;
		virtual int MinLength(T, T) = 0;
	};

	template <typename T>
	class GraphList :public Graph<T> {
	private:

		short int** Matrix;
	public:
		std::vector<std::vector<short int>> listOfEdges;

		std::vector<T> elementToNumberList;

		bool AddElement(T elementToAdd) override {
			short int listSize = listOfEdges.size();

			if (listSize == 0) {
				listOfEdges.push_back(std::vector<short int>());
				elementToNumberList.push_back(elementToAdd);
				return true;
			}

			for (int vectorIterator = 0; vectorIterator < listSize; vectorIterator++) {
				if (elementToNumberList[vectorIterator] == elementToAdd)
					return false;
			}
			listOfEdges.push_back(std::vector<short int>());
			elementToNumberList.push_back(elementToAdd);
			return true;
		}

		bool EraseElement(T elementToErase)override {
			int listSize = elementToNumberList.size();
			if (listSize == 0)
				return false;

			int elementToEraseNumber = -1;
			for (int vectorIterator = 0; vectorIterator < listSize; vectorIterator++)
				if (elementToNumberList[vectorIterator] == elementToErase) {
					elementToEraseNumber = vectorIterator;
					break;
				}

			if (elementToEraseNumber == -1)
				return false;

			int numberOfConnectedNodes = listOfEdges[elementToEraseNumber].size();
			for (int vectorIterator = 0; vectorIterator < numberOfConnectedNodes; vectorIterator++) {
				for (int connectedIterator = 0;
					connectedIterator < listOfEdges[listOfEdges[elementToEraseNumber][vectorIterator]].size();
					connectedIterator++) {
					if (listOfEdges[listOfEdges[elementToEraseNumber][vectorIterator]][connectedIterator] == elementToEraseNumber)
						listOfEdges[listOfEdges[elementToEraseNumber][vectorIterator]].erase(listOfEdges[listOfEdges[elementToEraseNumber][vectorIterator]].begin() + connectedIterator);
				}
			}

			listOfEdges.erase(listOfEdges.begin() + elementToEraseNumber);
			elementToNumberList.erase(elementToNumberList.begin() + elementToEraseNumber);
			return true;
		}

		bool CheckConnectivity() override {
			int listSize = elementToNumberList.size();
			int* fathers = new int[listSize];
			int* length = new int[listSize];
			bool* used = new bool[listSize];

			breadthFirstSearchForList(0, fathers, length, used);

			for (int i = 0; i < listSize; i++)
				if (!used)
					return false;
			return true;
		}

		int FindElement(T vertex) override {
			int listSize = elementToNumberList.size();
			for (int i = 0; i < listSize; i++)
				if (elementToNumberList[i] == vertex)
					return i;
			return -1;
		}

		bool BFS(int vertex, int fathers[], int length[], bool used[])override {
			std::queue<int> nodes;
			int listSize = elementToNumberList.size();
			for (int i = 0; i < listSize; i++) {
				fathers[i] = 0;
				length[i] = INT64_MAX;
				used[i] = false;
			}

			used[vertex] = true;
			fathers[vertex] = -1;
			nodes.push(vertex);

			while (nodes.empty() != true) {
				int cur_vertex = nodes.front();
				nodes.pop();

				int numberOfNodes = listOfEdges[cur_vertex].size();
				for (int vectorIterator = 0; vectorIterator < numberOfNodes; vectorIterator++) {
					int connectedNumber = listOfEdges[cur_vertex][vectorIterator];
					if (used[connectedNumber] == false) {
						used[connectedNumber] = true;
						nodes.push(connectedNumber);
						length[connectedNumber] = length[cur_vertex] + 1;
						fathers[connectedNumber] = cur_vertex;
					}
				}
			}
			return true;
		}


		int MinLength(T firstNode, T secondNode) override {
			int listSize = elementToNumberList.size();
			int* fathers = new int[listSize];
			int* length = new int[listSize];
			bool* used = new bool[listSize];

			int firstNumber = findNumberInList(firstNode);
			int secondNumber = findNumberInList(secondNode);
			if (firstNumber * secondNumber < 0)
				return -1;

			breadthFirstSearchForList(firstNumber, fathers, length, used);

			if (length[secondNumber] == INT64_MAX)
				return -1;
			else
				return length[secondNumber];

		}

		bool generateMatrixFromList() {
			int listSize = elementToNumberList.size();

			Matrix = new short int* [listSize];
			for (int i = 0; i < listSize; i++)
				Matrix[i] = new short int[listSize];
			for (int i = 0; i < listSize; i++)
				for (int j = 0; j < listSize; j++)
					Matrix[i][j] = 0;

			int numberOfNodes = 0;
			for (int vectorIterator = 0; vectorIterator < listSize; vectorIterator++) {
				numberOfNodes = listOfEdges[vectorIterator].size();
				for (int nodesIterator = 0; nodesIterator < numberOfNodes; nodesIterator++) {
					Matrix[vectorIterator][listOfEdges[vectorIterator][nodesIterator]] = 1;
					Matrix[listOfEdges[vectorIterator][nodesIterator]][vectorIterator] = 1;
				}
			}

			for (int vectorIterator = 0; vectorIterator < listSize; vectorIterator++)
				listOfEdges[vectorIterator].clear();
			listOfEdges.clear();
		}
	};
	template <typename T>
	class GraphMatrix :public GraphList<T> {
	private:
		short int** matrixOfEdges;
	public:
		bool AddElement(T elementToAdd) override {
			int listSize = elementToNumberList.size();
			if (listSize == 0) {
				matrixOfEdges = new short int* [1];
				matrixOfEdges[0] = new short int[1];
				matrixOfEdges[0][0] = 0;
				elementToNumberList.push_back(elementToAdd);
				return true;
			}
			for (int vectorIterator = 0; vectorIterator < listSize; vectorIterator++) {
				if (elementToNumberList[vectorIterator] == elementToAdd)
					return false;
			}
			matrixChangeNumberOfEdges(+1, listSize);
			elementToNumberList.push_back(elementToAdd);
			return true;
		}
		bool EraseElement(T elementToErase) override {
			int listSize = elementToNumberList.size();
			if (listSize == 0)
				return false;

			for (int vectorIterator = 0; vectorIterator < listSize; vectorIterator++) {
				if (elementToNumberList[vectorIterator] == elementToErase) {
					elementToNumberList.erase(elementToNumberList.begin() + vectorIterator);
					for (int columnIterator = 0; columnIterator < listSize; columnIterator++)
						for (int rowIterator = vectorIterator; rowIterator < listSize - 1; rowIterator++)
							matrixOfEdges[columnIterator][rowIterator] = matrixOfEdges[columnIterator][rowIterator + 1];
					for (int rowIterator = 0; rowIterator < listSize; rowIterator++)
						for (int columnIterator = vectorIterator; columnIterator < listSize - 1; columnIterator++)
							matrixOfEdges[columnIterator][rowIterator] = matrixOfEdges[columnIterator + 1][rowIterator];
					matrixChangeNumberOfEdges(-1, listSize);
				}
				return false;
			}

			return false;
		}

		bool CheckConnectivity() override {
			int listSize = elementToNumberList.size();
			int* fathers = new int[listSize];
			int* length = new int[listSize];
			bool* used = new bool[listSize];

			breadthFirstSearchForMatrix(0, fathers, length, used);

			for (int i = 0; i < listSize; i++)
				if (!used)
					return false;
			return true;
		}
		int findNumberInList(TNodeType vertex) {
			int listSize = elementToNumberList.size();
			for (int i = 0; i < listSize; i++)
				if (elementToNumberList[i] == vertex)
					return i;
			return -1;
		}

		bool BFS(int vertex, int fathers[], int length[], bool used[]) override {
			std::queue<int> nodes;
			int listSize = elementToNumberList.size();
			for (int i = 0; i < listSize; i++) {
				fathers[i] = 0;
				length[i] = INT64_MAX;
				used[i] = false;
			}

			used[vertex] = true;
			fathers[vertex] = -1;
			nodes.push(vertex);

			while (nodes.empty() != true) {
				int curVertex = nodes.front();
				nodes.pop();

				for (int curNode = 0; curNode < listSize; curNode++) {
					if (matrixOfEdges[curVertex][curNode] != 0)
						if (used[curNode] == false) {
							used[curNode] = true;
							nodes.push(curNode);
							length[curNode] = length[curVertex] + 1;
							fathers[curNode] = curVertex;
						}
				}
			}
			return true;
		}

		int MinLength(T firstNode, T secondNode) override {
			int listSize = elementToNumberList.size();
			int* fathers = new int[listSize];
			int* length = new int[listSize];
			bool* used = new bool[listSize];

			int firstNumber = findNumberInList(firstNode);
			int secondNumber = findNumberInList(secondNode);

			breadthFirstSearchForMatrix(firstNumber, fathers, length, used);

			if (length[secondNumber] == INT64_MAX)
				return -1;
			else
				return length[secondNumber];
		}

		bool generateListFromMatrix() {
			int listSize = elementToNumberList.size();

			listOfEdges.reserve(listSize);

			for (int i = 0; i < listSize; i++)
				for (int j = i; j < listSize; j++)
					if (matrixOfEdges[i][j] == 1) {
						listOfEdges[i].push_back(j);
						listOfEdges[j].push_back(i);
					}

			for (int i = 0; i < listSize; i++)
				delete matrixOfEdges[i];
			delete[] matrixOfEdges;
		}

	};
