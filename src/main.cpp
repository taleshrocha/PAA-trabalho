#include "../include/RCPSP.h"
#include "../include/BacktrackTree.h"
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
using bc::BacktrackTree;
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

void printSchedule(vector<vector<int>> schedule) {
  if (schedule.empty()) {
    cout << "Running tasks [numPeriod=" << 1 << "]: {}" << endl;
  }

    for (auto i = 0; i < schedule.size(); i++) {
        cout << "Running tasks [numPeriod=" << i + 1 << "]: {";
        for (auto j = 0; j < schedule[i].size(); j++) {
          if (j == schedule[i].size()-1) {
            cout << schedule[i][j];
            break;
          }
          cout << schedule[i][j] << ", ";
        }
        cout << "}" << endl;
    }
}

vector<vector<int>> allTaskCombinations(
    RCPSP<int>* G, 
    vector<int> resources,
    vector<int> availableTasks
  ) {

    vector<vector<int>> allTaskCombinations;

    auto task = availableTasks.begin();
    while (task != availableTasks.end()) {

      if (G->hasResoucesForTask(*task, resources)) {
        //auto taskVertex = G->findVertex(*task);

        /*
        for (int i = 0; i < 4; i++) {
          resources[i] -= (*taskVertex)->resourcesRequired[i];
        }
        */

        vector<int> taskCombination;
        taskCombination.push_back(*task);

        task = availableTasks.erase(task);

        allTaskCombinations.push_back(taskCombination);
      } else {
        task++;
      }
    }

    return allTaskCombinations;
}

vector<vector<int>> scheduleTasks(
    RCPSP<int>* G, 
    vector<int> resources,
    vector<vector<int>> schedule,
    vector<int> availableTasks,
    vector<int> runningTasks,
    vector<int> inDegrees,
    vector<int> durations
  ) {

    // Caso base
    if (availableTasks.empty() && runningTasks.empty()) {
      return schedule;
    }

    vector<int> newSchedulePart;
    vector<vector<int>> bestSchedule;

    // Atualiza as tarefas que estão executando
    auto task = runningTasks.begin();
    while (task != runningTasks.end()) {
      durations[*task - 1]--;

      if (durations[*task - 1] > 0) {
        newSchedulePart.push_back(*task);
        task++;
      } else {
        G->taskCompleted(*task, availableTasks, inDegrees);
        auto taskVertex = G->findVertex(*task);

        for (int i = 0; i < 4; i++) {
          resources[i] += (*taskVertex)->resourcesRequired[i];
        }

        task = runningTasks.erase(task);
      }
    }


    /*
    auto newSchedule1 = schedule;
    newSchedule1.push_back(newSchedulePart);

    auto backtrackSchedule1 = scheduleTasks(G, resources, newSchedule1, availableTasks, runningTasks, 
      inDegrees, durations, bestSchedule, level);
    
      bestSchedule = backtrackSchedule1;
*/

    auto tasksCombinations = allTaskCombinations(G, resources, availableTasks);
    cout << endl;
    printSchedule(tasksCombinations);

    for (auto taskCombination : tasksCombinations) {

      auto task = taskCombination.begin();
      while (task != taskCombination.end()) {
        runningTasks.push_back(*task);
        task = availableTasks.erase(task);
        task++;
      }

      auto newSchedule = schedule;
      newSchedule.push_back(taskCombination);

      auto backtrackSchedule = scheduleTasks(G, resources, newSchedule, availableTasks, runningTasks, 
        inDegrees, durations);
      
      if(bestSchedule.empty() || backtrackSchedule.size() < bestSchedule.size()) {
        bestSchedule = backtrackSchedule;
      }

    }

    return bestSchedule;
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
        /*
        cout << G.toString() << endl;
        return 0;
        */

        microseconds durationScheduleTasks(0);
        auto startScheduleTasks = high_resolution_clock::now();

        vector<vector<int>> S = scheduleTasks(
            &G, 
            resourceAvailabilities,
            vector<vector<int>>(),
            G.availableTasks(),
            vector<int>(),
            G.getInDegrees(),
            G.getDurations()
          );

        auto stopScheduleTasks = high_resolution_clock::now();
        durationScheduleTasks = duration_cast<microseconds>(stopScheduleTasks - startScheduleTasks);

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
