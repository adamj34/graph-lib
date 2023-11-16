#ifndef ALGORITHMS_MST_IMST_HPP
#define ALGORITHMS_MST_IMST_HPP

#include <vector>
#include <map>

class IMst {
public:
    virtual ~IMst() = default;
    virtual void solve(int source = 0) = 0;
    virtual int get_cost() const = 0;
    virtual const std::map<int, std::vector<int>>& get_mst() const = 0;
};


#endif // ALGORITHMS_MST_IMST_HPP
