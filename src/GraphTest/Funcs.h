#pragma once

#include "Cclass.h"

bool ConnectedGraph(vector<vector<edge>> &H);
void Renumerate(vector<vector<edge>> &H, int s, int t);
edge PairwiseConnectivity(vector<vector<edge>> &H, edge F, bool connected);
vector<int> GetNodePowers(vector<vector<edge>> &H);
void RemoveNode(vector<vector<edge>> &H, int q);
void ContractEdge(vector<vector<edge>> &H, int q, int w);
bool ElementInside(vector<int> P, int x);
vector<int> GetChain(vector<vector<edge>> &H, vector<int> &checkedNodes);
edge ChainReduction1(vector<vector<edge>> &H, edge sum, vector<int> checkedNodes, bool connected);
edge ChainReduction2(vector<vector<edge>> &H, edge sum, vector<int> weight, bool connected);
