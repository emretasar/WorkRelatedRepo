#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib> 
#include <sstream> 
#include <vector>

void readInsText(std::vector<std::pair<int, int>>& insIndexContent) {
    std::ifstream inputFile("ins.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    int offset, sec, nsec, subaddress;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        lineStream >> offset >> sec >> nsec >> subaddress;
        int totalNanoseconds = sec * 1000000000 + nsec;
        if (subaddress == 4) {
            insIndexContent.push_back(std::make_pair(offset, totalNanoseconds));
        }
    }
    inputFile.close();
}

void readUdpText(std::vector<std::pair<int, int>>& udpIndexContent) {
    std::ifstream inputFile("udp.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file!" << std::endl;
        return;
    }

    int offset, sec, nsec;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        lineStream >> offset >> sec >> nsec;
        int totalNanoseconds = sec * 1000000000 + nsec;
        udpIndexContent.push_back(std::make_pair(offset, totalNanoseconds));

    }
    inputFile.close();
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> matchElements(
    const std::vector<std::pair<int, int>>& list1,
    const std::vector<std::pair<int, int>>& list2,
    int threshold)
{
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> matchedPairs;
    int i = 0, j = 0;

    while (i < list1.size() && j < list2.size()) {
        int diff = std::abs(list1[i].second - list2[j].second);

        if (diff <= threshold) {
            if (j + 1 < list2.size() && std::abs(list1[i].second - list2[j + 1].second) < diff) {
                j++;
                continue;
            }
            matchedPairs.push_back({ list1[i], list2[j] });
            i++;
            j++;
        }
        else {
            if (list1[i].second < list2[j].second) {
                i++;
            }
            else {
                j++;
            }
        }
    }

    return matchedPairs;
}
int main() {
    std::vector<std::pair<int, int>> insIndexCont;
    std::vector<std::pair<int, int>> udpIndexCont;
    readInsText(insIndexCont);
    readUdpText(udpIndexCont);
    
    auto matchedElements = matchElements(insIndexCont, udpIndexCont, 100);

    for (const auto& match : matchedElements) {
        std::cout << match.first.first << " " << match.first.second << " " << match.second.first << " " << match.second.second << std::endl;

    }
}
