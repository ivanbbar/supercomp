#include <iostream>
#include <vector>

struct Item {
    int id;
    double weight;
    double value;
};

int num_leaf = 0, num_copy = 0;

double knapsack(int capacity, const std::vector<Item>& items, std::vector<Item>& used) {
    if (items.empty() || capacity == 0)
        return 0;

    double current_value = 0.0, best_value = 0.0;
    for (const auto& item : used)
        current_value += item.value;
    for (const auto& item : items)
        best_value += item.value;

    if (current_value + best_value <= num_copy)
        return 0;

    double max_value = 0.0;
    auto max_iter = items.begin();
    for (auto iter = items.begin(); iter != items.end(); ++iter) {
        if (iter->weight <= capacity && iter->value / iter->weight > max_value) {
            max_value = iter->value / iter->weight;
            max_iter = iter;
        }
    }

    std::vector<Item> new_items(items.begin(), max_iter);
    new_items.insert(new_items.end(), max_iter + 1, items.end());

    used.push_back(*max_iter);
    num_leaf++;

    if (current_value + max_iter->value > best_value) {
        num_copy++;
        best_value = current_value + max_iter->value;
    }

    return std::max(max_iter->value + knapsack(capacity - max_iter->weight, new_items, used),
                    knapsack(capacity, new_items, used));
}

int main() {
    int n, capacity;
    std::cin >> n >> capacity;

    std::vector<Item> items;
    items.reserve(n);
    for (int i = 0; i < n; i++) {
        double weight, value;
        std::cin >> weight >> value;
        items.push_back({i, weight, value});
    }

    std::vector<Item> used;
    double result = knapsack(capacity, items, used);

    std::cout << "RESULT: " << result << '\n';
    std::cout << "ELEMENTS IN THE BAG: ";
    for (const auto& item : used)
        std::cout << item.id << ' ';
    std::cout << "\nNUM_LEAF = " << num_leaf << "\nNUM_COPY = " << num_copy << '\n';

    return 0;
}
