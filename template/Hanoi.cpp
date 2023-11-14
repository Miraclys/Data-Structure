#include <iostream>
#include "./Stack.hpp"

class State {
    private:
        int n;
        char source;
        char auxiliary;
        char target;
    public:
        State(): n(0), source(' '), auxiliary(' '), target(' ') {}
        State(int N, char s, char t, char a): n(N), source(s), auxiliary(a), target(t) {}
        int getN() const {
            return n;
        }
        char getSource() const {
            return source;
        }
        char getAuxiliary() const {
            return auxiliary;
        }
        char getTarget() const {
            return target;
        }
        friend std::ostream& operator<<(std::ostream& os, const State& state) {
            os << "Move from " << state.source << " to " << state.target;
            return os;
        }
};

void solveHanoi(int n, char source, char target, char auxiliary) {
    Stack<State> s;
    s.push(State(n, source, target, auxiliary));
    while (!s.empty()) {
        State cur = s.top();
        s.pop();
        if (cur.getN() == 1) {
            std::cout << cur << std::endl;
        } else {
            char src = cur.getSource();
            char aux = cur.getAuxiliary();
            char tar = cur.getTarget();
            s.push(State(cur.getN() - 1, aux, tar, src));
            s.push(State(1, src, tar, aux));
            s.push(State(cur.getN() - 1, src, aux, tar));
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    solveHanoi(n, 'a', 'c', 'b');
    return 0;
}