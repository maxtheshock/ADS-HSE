#include <iostream>
#include <vector>

struct Robot {
    int id;
    int capacity;
};

struct RadixStorage {
    std::vector<Robot> buffer;
    std::vector<int> buckets;
};

constexpr int kByteBase = 256;
constexpr int kByteMask = 255;
constexpr int kBitsInByte = 8;
constexpr int kPassCount = 4;

int getByteDigit(int value, int pass) {
    return (value >> (pass * kBitsInByte)) & kByteMask;
}

void resetBuckets(std::vector<int>& buckets) {
    for (int i = 0; i < kByteBase; ++i) {
        buckets[i] = 0;
    }
}

void convertCountsToPositions(std::vector<int>& buckets) {
    int position = 0;

    for (int digit = 0; digit < kByteBase; ++digit) {
        const int count = buckets[digit];
        buckets[digit] = position;
        position += count;
    }
}

void radixPass(std::vector<Robot>& robots, RadixStorage& storage, int pass) {
    resetBuckets(storage.buckets);

    const int robot_count = static_cast<int>(robots.size());

    for (int i = 0; i < robot_count; ++i) {
        const int digit = getByteDigit(robots[i].capacity, pass);
        ++storage.buckets[digit];
    }

    convertCountsToPositions(storage.buckets);

    for (int i = 0; i < robot_count; ++i) {
        const int digit = getByteDigit(robots[i].capacity, pass);
        storage.buffer[storage.buckets[digit]] = robots[i];
        ++storage.buckets[digit];
    }

    robots.swap(storage.buffer);
}

void sortRobotsByCapacity(std::vector<Robot>& robots) {
    RadixStorage storage;
    storage.buffer.resize(robots.size());
    storage.buckets.assign(kByteBase, 0);

    for (int pass = 0; pass < kPassCount; ++pass) {
        radixPass(robots, storage, pass);
    }
}

void readRobots(std::vector<Robot>& robots) {
    const int robot_count = static_cast<int>(robots.size());

    for (int i = 0; i < robot_count; ++i) {
        std::cin >> robots[i].id >> robots[i].capacity;
    }
}

void printRobots(const std::vector<Robot>& robots) {
    for (const Robot& robot : robots) {
        std::cout << robot.id << '\t' << robot.capacity << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    std::cin >> n;

    std::vector<Robot> robots(n);
    readRobots(robots);

    sortRobotsByCapacity(robots);
    printRobots(robots);

    return 0;
}
