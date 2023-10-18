#include "../include/RCPSP.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <chrono>
#include <stdlib.h>
#include <algorithm> 

using sc::RCPSP;
using namespace std::chrono;
using namespace std;

struct ProjectInformation {
  int projectNumber;
  int numJobs;
  int relativeDate;
  int dueDate;
  int tardinessCost;
  int mpmTime;
};

void readInputFile(std::ifstream& inputFile, RCPSP<int>& G, ProjectInformation& projectInfo, std::vector<int>& resourceAvailabilities) {
  std::string line;
  int a, b, c;

  while (getline(inputFile, line)) {
    if (line.empty())
      continue;

    if (line.find("PROJECT INFORMATION:") != string::npos) {
      getline(inputFile, line);

      inputFile >> projectInfo.projectNumber >> projectInfo.numJobs
                  >> projectInfo.relativeDate >> projectInfo.dueDate
                  >> projectInfo.tardinessCost >> projectInfo.mpmTime;

    } else if (line.find("PRECEDENCE RELATIONS:") != string::npos) {
      getline(inputFile, line);
      while (getline(inputFile, line) && line.find("*") == string::npos) {
          istringstream iss(line);
          iss >> a >> b >> c;
          for (int i = 0; i < c; i++) {
            iss >> b;
            // Populates the graph.
            G.addEdge(make_pair(a, b));
          }
      }
    } else if (line.find("REQUESTS/DURATIONS:") != string::npos) {
      getline(inputFile, line);
      getline(inputFile, line);
      while (getline(inputFile, line) && line.find("*") == string::npos) {
          istringstream iss(line);
          iss >> a >> b >> c;
          G.setDuration(a, c);
          auto aux = G.findVertex(a);
          for (int i = 0; i < 4; i++)
            iss >> (*aux)->resourcesRequired[i];
      }
    } else if (line.find("RESOURCEAVAILABILITIES:") != string::npos) {
      getline(inputFile, line);
      getline(inputFile, line);
      istringstream iss(line);
      for (int i = 0; i < 4; i++)
            iss >> resourceAvailabilities[i];
    }
  }
}

vector<vector<int>> scheduleTasks(RCPSP<int>* G, vector<int> resources) {
  vector<vector<int>> schedule; //(G->size(), vector<int>(G->totalDuration(), 0));
  vector<int> availableTasks = G->availableTasks();
  vector<int> runningTasks;
  //int numPeriods = 0;

  vector<int> durations = G->getDurations();
  vector<int> inDegrees = G->getInDegrees();

  while (!availableTasks.empty() || !runningTasks.empty()) {
    vector<int> temp;

    auto it = runningTasks.begin();
    while (it != runningTasks.end()) {
      durations[*it-1]--;
      if (durations[*it-1] > 0) {
        //schedule[*it-1][numPeriods] = 1;
        temp.push_back(*it);
        it++;
      } else {
        G->taskCompleted(*it, availableTasks, inDegrees);
        auto aux = G->findVertex(*it);
        for (int i = 0; i < 4; i++)
          resources[i] += (*aux)->resourcesRequired[i];

        it = runningTasks.erase(it);
      }
    }

    auto it2 = availableTasks.begin();
    while (it2 != availableTasks.end()) {
      if (G->isTaskAvailable(*it2, resources)) {
        auto aux = G->findVertex(*it2);
        for (int i = 0; i < 4; i++)
          resources[i] -= (*aux)->resourcesRequired[i];

        //schedule[*it2-1][numPeriods] += 1;
        temp.push_back(*it2);
        runningTasks.push_back(*it2);
        it2 = availableTasks.erase(it2);
      } else
        it2++;
    }
    //numPeriods++;
    if (!availableTasks.empty() || !runningTasks.empty())
      schedule.push_back(temp);
  }
  
  return schedule;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Error: Test case file not informed!" << endl;
    return 1;
  }

  std::ifstream inputFile(argv[1]);
  srand (time(NULL));

  if (!inputFile) {
    cerr << "Error: Could not open file '" << argv[1] << "' or it doesn't exist!" << endl;
    return 2;
  }

  try {
        RCPSP<int> G;
        ProjectInformation projectInfo;
        vector<int> resourceAvailabilities(4, 0);

        // Read input
        readInputFile(inputFile, G, projectInfo, resourceAvailabilities);

        microseconds durationScheduleTasks(0);
        auto startScheduleTasks = high_resolution_clock::now();

        // Schedule tasks
        vector<vector<int>> S = scheduleTasks(&G, resourceAvailabilities);

        auto stopScheduleTasks = high_resolution_clock::now();
        durationScheduleTasks = duration_cast<microseconds>(stopScheduleTasks - startScheduleTasks);

        /*
          Output the results
        */
        //cout << G.toString() << endl;

     string fileName = argv[1];
     std::replace( fileName.begin(), fileName.end(), '/', '-');
     string fileFolder = "log-files";
     auto arg = fileFolder + "/" + fileName + ".log";
     cout << arg << endl;

     std::ofstream file(arg);

        cout << "Makespan: " << S.size() << endl;
        file << "Makespan: " << S.size() << endl;

        cout << "Time: " << durationScheduleTasks.count() << " microseconds" << endl;
        file << "Time: " << durationScheduleTasks.count() << " microseconds" << endl;

        cout << "Task schedule considering resource constraints and precedence relations:" << endl;
        file << "Task schedule considering resource constraints and precedence relations:" << endl;

        for (auto i = 0; i < S.size(); i++) {
            cout << "Running tasks [numPeriod=" << i + 1 << "]: {";
            file << "Running tasks [numPeriod=" << i + 1 << "]: {";
            for (auto j = 0; j < S[i].size(); j++) {
              if (j == S[i].size()-1) {
                cout << S[i][j];
                file << S[i][j];
                break;
              }
              cout << S[i][j] << ", ";
              file << S[i][j] << ", ";
            }
            cout << "}" << endl;
            file << "}" << endl;
        }

     file.close();

    } catch (const std::exception& e) {
        cerr << "An exception occurred: " << e.what() << endl;
        return 1;
    }

    return 0;
}
