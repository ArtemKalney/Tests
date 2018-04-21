#pragma once

#include "stdafx.h"

class Branche
{
private:
    std::vector<double> _C;
    int _power;
    int _firstNode;
    int _secondNode;
    int _simple;
    bool _isReliable;
public:
    Branche() {}

    Branche(std::vector<double> C, const int& power, const int& firstNode, const int& secondNode, const int& simple,
            bool isReliable) :
            _C(std::move(C)),
            _power(power),
            _firstNode(firstNode),
            _secondNode(secondNode),
            _simple(simple),
            _isReliable(isReliable)
    {}
    //copy
    Branche(const Branche& branch) :
            _C(branch._C),
            _power(branch._power),
            _firstNode(branch._firstNode),
            _secondNode(branch._secondNode),
            _simple(branch._simple),
            _isReliable(branch._isReliable)
    {}

    void SetC(const std::vector<double>& C)
    {
        _C = C;
    }

    std::vector<double>& GetC()
    {
        return _C;
    }

    void SetPower(const int& power)
    {
        _power = power;
    }

    int GetPower() const
    {
        return _power;
    }

    void SetFirstNode(const int& firstNode)
    {
        _firstNode = firstNode;
    }

    int GetFirstNode() const
    {
        return _firstNode;
    }

    void SetSecondNode(const int& secondNode)
    {
        _secondNode = secondNode;
    }

    int GetSecondNode() const
    {
        return _secondNode;
    }

    void SetSimple(const int& simple)
    {
        _simple = simple;
    }

    int GetSimple() const
    {
        return _simple;
    }

    void SetIsReliable(bool isReliable)
    {
        _isReliable = isReliable;
    }

    bool GetIsReliable() const
    {
        return _isReliable;
    }

    static Branche GetBranch (const int& firstNode, const int& secondNode, const int& power);
    static Branche GetBranch (const int& vectorSize, const int& power);
    static Branche GetBranch (const int& power);
    static Branche GetSimpleBranch (const int& firstNode, const int& secondNode);
    static Branche GetSimpleBranch ();
    static Branche GetZero ();
    static Branche GetUnity ();
    static bool EqualNodes (const Branche& firstBranche, const Branche& secondBranche);
    static bool EqualNodes (const Branche& branche, const int& firstNode, const int& secondNode);
    static bool EqualNodes (const int& firstBranchNode, const int& secondBranchNode, const int& firstNode,
                            const int& secondNode);
    static void ParallelReduction(Branche& branche);
    static bool IsUnacceptableBranche(Branche& branche);

    bool IsExisting() const;
    bool IsUnity();
    void PrintBranche();
    bool IsSimpleBranch();
};

Branche operator *(Branche firstBranch, Branche secondBranch);
Branche operator +(Branche firstBranch, Branche secondBranch);
Branche operator -(Branche firstBranch, Branche secondBranch);
Branche operator ~(Branche branche);