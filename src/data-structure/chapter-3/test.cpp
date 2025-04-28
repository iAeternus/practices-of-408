#include <bits/stdc++.h>

/**
 * @see 84-02
 */
void reverse(std::queue<int>& q) {
    std::stack<int> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
}

auto should_reverse = []() {
    // Given
    std::queue<int> q;
    q.push(1), q.push(2), q.push(3), q.push(4), q.push(5);

    // When
    reverse(q);
    
    // Then
    while(!q.empty()) {
        std::cout << q.front() << ' ';
        q.pop();
    }
    std::cout << std::endl;
};

void separator() {
    std::cout << "=============================================\n";
}

int main() {
    should_reverse();
    separator();
}