#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

struct pdata {
    int ts, te;
    int sid, rid;
    vector<pair<float, float>> gg;
};

struct ppass {
    int numpass = 0;
};

struct teamdat {
    unordered_map<int, ppass> players;
    int tp = 0;
};

struct matchdat {
    teamdat g1, g2;
};

bool checkpos(const vector<pair<float, float>>& d1, const vector<pair<float, float>>& d2) {
    if (d1.size() != d2.size()) {
        return false;
    }
    for (size_t i = 0; i < d1.size(); ++i) {
        if (d1[i].first != d2[i].first || d1[i].second != d2[i].second) return false;
    }
    return true;
}

bool checktime(int t1_start, int t1_end, int t2_start, int t2_end, int range = 300) {
    return (std::abs(t1_start - t2_start) <= range || std::abs(t1_end - t2_end) <= range);
}

int main() {
    ifstream file("passes.csv");
    if (!file.is_open()) {
        return 1;
    }

    string line;
    vector<pdata> passes;

    while (getline(file, line)) {
        stringstream f(line);
        pdata pass;
        string val;

        try {
            getline(f, val, ',');
            pass.ts = stoi(val);

            getline(f, val, ',');
            pass.te = stoi(val);

            getline(f, val, ',');
            pass.sid = stoi(val);

            getline(f, val, ',');
            pass.rid = stoi(val);

            for (int i = 0; i < 28; ++i) {
                float x, y;
                getline(f, val, ',');
                if (val.empty()) continue;
                x = stof(val);
                getline(f, val, ',');
                y = stof(val);
                pass.gg.emplace_back(x, y);
            }

            passes.push_back(pass);
        }
        catch (const exception& e) {
            continue;
        }
    }

    vector<matchdat> matches;

    for (const auto& pass : passes) {
        bool added_to_match = false;
        for (auto& match : matches) {
            if (checktime(pass.ts, pass.te, match.g1.tp, match.g2.tp)) {
                for (const auto& prev_pass : passes) {
                    if (checkpos(pass.gg, prev_pass.gg)) {
                        added_to_match = true;
                        break;
                    }
                }
            }
        }

        if (!added_to_match) {
            if (matches.size() < 14) {
                matchdat new_match;
                matches.push_back(new_match);
            }
        }
    }

    for (const auto& pass : passes) {
        for (auto& match : matches) {
            if ((pass.sid >= 1 && pass.sid <= 14 && pass.rid >= 1 && pass.rid <= 14) ||
                (pass.sid >= 15 && pass.sid <= 28 && pass.rid >= 15 && pass.rid <= 28)) {
                if (pass.sid >= 1 && pass.sid <= 14) {
                    match.g1.players[pass.sid].numpass++;
                    match.g1.tp++;
                }
                else if (pass.sid >= 15 && pass.sid <= 28) {
                    match.g2.players[pass.sid].numpass++;
                    match.g2.tp++;
                }
            }
        }
    }

    for (size_t i = 0; i < matches.size(); ++i) {
        const auto& match = matches[i];
        cout << "******** " << "Match " << i + 1 << " ********" << endl;

        cout << "      TEAM 1:" << endl;
        for (const auto& player : match.g1.players) {
            int id = player.first;
            const ppass& stats = player.second;
            if (match.g1.tp > 0) {
                float percentage = (stats.numpass / static_cast<float>(match.g1.tp)) * 100;
                cout << "Team 1 Player " << id << ": " << fixed << setprecision(2) << percentage << "%\n";
            }
        }
        cout << "     TEAM 2:" << endl;
        for (const auto& player : match.g2.players) {
            int id = player.first;
            const ppass& stats = player.second;
            if (match.g2.tp > 0) {
                float percentage = (stats.numpass / static_cast<float>(match.g2.tp)) * 100;
                cout << "Team 2 Player " << id << ": " << fixed << setprecision(2) << percentage << "%\n";
            }
        }
    }

    return 0;
}
