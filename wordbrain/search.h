#ifndef WORDBRAIN_SEARCH_H_INCLUDED
#define WORDBRAIN_SEARCH_H_INCLUDED

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace detail {

// reverse by cost less.
template <class T> bool FirstMore(const std::pair<int, T>& a, const std::pair<int, T>& b) {
    return a.first > b.first;
}

template <class State, class GetSuccessors, class IsDone, class Cost> State Iterate(std::vector<std::pair<int, State>> queue, GetSuccessors get_successors, IsDone done, Cost cost) {
    while(true) {
        assert(!queue.empty());
        // pop least cost element
        std::pop_heap(queue.begin(), queue.end(), FirstMore<State>);

        const State& cur = queue.back().second; 
        if(done(cur)) return cur;

        std::vector<State> new_candidates = get_successors(cur);
        queue.pop_back();

        for(const State& new_candidate : new_candidates) {
            queue.push_back(std::make_pair(cost(new_candidate), new_candidate));
            std::push_heap(queue.begin(), queue.end(), FirstMore<State>);
        }
        std::cerr << "queue depth: " << queue.size() << "\n";
    }
}

}  // namespace detail

// TODO: Not actually that helpful because it keeps state internal, so there's no "continue" once it finds a solution.
// GetSuccessors must be a functor that returns a container of states from a const State&.
// IsDone must be a functor that evaluates a const State& for completion.
template <class State, class GetSuccessors, class IsDone, class Cost> State Search(State initial, GetSuccessors get_successors, IsDone done, Cost cost) {
    std::vector<std::pair<int, State>> queue;
    queue.push_back(std::make_pair(cost(initial), initial));
    return detail::Iterate(queue, get_successors, done, cost);
}

#endif  // defined WORDBRAIN_SEARCH_H_INCLUDED
