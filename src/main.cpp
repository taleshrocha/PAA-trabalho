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
#include <utility>
#include <random>

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

/*void printSchedule(vector<vector<int>> schedule) {
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
}*/

/*vector<vector<int>> allTaskCombinations(
    RCPSP<int>* G, 
    vector<int> resources,
    vector<int> availableTasks,
    vector<int> node
  ) {
    vector<vector<int>> solution;
    auto task = availableTasks.begin();
    while (task != availableTasks.end()) {
      if (G->hasResoucesForTask(*task, resources)) {
        auto newResources = resources;
        auto taskVertex = G->findVertex(*task);

        for (int i = 0; i < 4; i++) {
          newResources[i] -= (*taskVertex)->resourcesRequired[i];
        }

        auto newNode = node;
        newNode.push_back(*task);
        solution.push_back(newNode);

        std::vector<int> newAvailableTasks(task+1, availableTasks.end());
        auto partialSolution = allTaskCombinations(G, newResources, newAvailableTasks, newNode);
        for (auto taskList : partialSolution) {
          solution.push_back(taskList);
        }
      } 
      task++;
    }
    return solution;
}*/

/*vector<vector<int>> scheduleTasks(
    RCPSP<int>* G, 
    vector<int> resources,
    vector<vector<int>> schedule,
    vector<int> availableTasks,
    vector<int> runningTasks,
    vector<int> inDegrees,
    vector<int> durations,
    int level = -2
  ) {
    level++;

    // Caso Base
    if (availableTasks.empty() && runningTasks.empty()) {
      // cout << "!!!! FOUND SOLUTION !!!! - " << level << endl;
      // printSchedule(schedule);
      return schedule;
    }

    vector<int> newSchedulePart;
    vector<vector<int>> bestSchedule;
    vector<int> newInDegrees = inDegrees;

    // Atualiza as tarefas que estão executando
    auto task = runningTasks.begin();
    while (task != runningTasks.end()) {
      durations[*task - 1]--;

      if (durations[*task - 1] > 0) {
        newSchedulePart.push_back(*task);
        task++;
      } else {
        G->taskCompleted(*task, availableTasks, newInDegrees);
        auto taskVertex = G->findVertex(*task);

        for (int i = 0; i < 4; i++) {
          resources[i] += (*taskVertex)->resourcesRequired[i];
        }

        task = runningTasks.erase(task);
      }
    }

    auto tasksCombinations = 
      allTaskCombinations(G, resources, availableTasks, vector<int>());

    vector<vector<int>> newSchedule = schedule;
    vector<int> newRunningTasks, newAvailableTasks, newResources;

    // Caso em que não tem nenhuma taks disponível para ser feita, mas tem task executando
    if(tasksCombinations.empty()) {
      if(!newSchedulePart.empty())
        newSchedule.push_back(newSchedulePart);

      return scheduleTasks(G, resources, newSchedule, availableTasks, 
      runningTasks, newInDegrees, durations, level);
    }

    for (vector<int> taskCombination : tasksCombinations) {
      newSchedule = schedule;
      newRunningTasks = runningTasks;
      newAvailableTasks = availableTasks;

      // Colocar cada uma das tarefas para executar nesse estado
      auto temp = newSchedulePart;
      auto task = taskCombination.begin();
      newResources = resources;
      while (task != taskCombination.end()) {
        newRunningTasks.push_back(*task);
        temp.push_back(*task);

        auto taskVertex = G->findVertex(*task);
        for (int i = 0; i < 4; i++) {
          newResources[i] -= (*taskVertex)->resourcesRequired[i];
        }
        
        auto it = find(newAvailableTasks.begin(), newAvailableTasks.end(), *task);
        if (it != newAvailableTasks.end()) {
            newAvailableTasks.erase(it);
        }
        task++;
      }
      newSchedule.push_back(temp);

      if (bestSchedule.empty() || newSchedule.size() < bestSchedule.size()) {
        auto backtrackSchedule = scheduleTasks(G, newResources, newSchedule, newAvailableTasks, 
                                                newRunningTasks, newInDegrees, durations, level);

        if (bestSchedule.empty() || backtrackSchedule.size() < bestSchedule.size()) {
            bestSchedule = backtrackSchedule;
        }
      }
    }

    return bestSchedule;
}*/

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

vector<vector<int>> modifyScheduleRepresentation(RCPSP<int>* G, vector<vector<int>> schedule, int op=0) {
  if (op == 0) {
    vector<vector<int>> s(G->size(), vector<int>(G->totalDuration(), 0));
    for(int i=0; i < schedule.size(); i++) {
      for(int task : schedule[i]){
        s[task-1][i] = 1;
      }
    }
    return s;
  } else {
    vector<vector<int>> s;
    for(int i=0; i<G->totalDuration(); i++) {
      vector<int> aux;
      for(int j=0; j<G->size(); j++) {
        if(schedule[j][i] == 1)
          aux.push_back(j+1);
      }
      if(!aux.empty())
        s.push_back(aux);
    }
    return s;
  }
}

bool isTabu(pair<int,int> scheduleSwap, vector<pair<int,int>> tabuList) {
  auto found = find_if(tabuList.begin(), tabuList.end(),
    [scheduleSwap](pair<int, int>& tabu) {
        return (tabu.first == scheduleSwap.first && tabu.second == scheduleSwap.second) ||
                (tabu.first == scheduleSwap.second && tabu.second == scheduleSwap.first);
    });

  return found != tabuList.end();
}

bool isValidSchedule(RCPSP<int>* G, vector<vector<int>> currSchedule, int task1, int task2, int task1Start, int task2Start, vector<int> resources) {
  for(int i=0; i<G->totalDuration(); i++) {
    vector<int> temp = resources;
    for(int j=0; j<G->size(); j++) {
      if(currSchedule[j][i] == 1) {
        auto aux3 = G->findVertex(j+1);
        for (int k = 0; k < 4; k++)
          temp[k] -= (*aux3)->resourcesRequired[k];
      }
    }
    for (int k = 0; k < temp.size(); k++) {
      if(temp[k] < 0)
        return false;
    }
  }

  for(int aux : (*G->findVertex(task1))->pred) {
    for(int j=0; j<G->totalDuration(); j++) {
      if(currSchedule[aux-1][j] == 1 && j>=task1Start)
        return false;
    }
  }

  for(int aux : (*G->findVertex(task2))->pred) {
    for(int j=0; j<G->totalDuration(); j++) {
      if(currSchedule[aux-1][j] == 1 && j>=task2Start)
        return false;
    }
  }
  return true;
}

vector<vector<int>> generateNeighbour(RCPSP<int>* G, vector<vector<int>> currSchedule, vector<pair<int,int>> & tabuList, vector<int> resources) {
  vector<vector<int>> modifiedSchedule = modifyScheduleRepresentation(G, currSchedule);
  int task1, task2;
  int task1Start, task2Start, numTentativas = 0;
  vector<vector<int>> modifiedScheduleAux;
  do {
    modifiedScheduleAux = modifiedSchedule;
    task1Start = 0, task2Start = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(2, G->size() - 1);

    task1 = dis(gen);
    task2 = dis(gen);

    while (task1 == task2 || isTabu(make_pair(task1, task2), tabuList)) {
        task2 = dis(gen);
    }
    
    for(int i=0; i<G->totalDuration(); i++) {
      if (modifiedScheduleAux[task1-1][i] == 1 && task2Start == 0)
        task2Start = i;

      if (modifiedScheduleAux[task2-1][i] == 1 && task1Start == 0)
        task1Start = i;

      swap(modifiedScheduleAux[task1-1][i], modifiedScheduleAux[task2-1][i]);
    }

    if (task1Start == task2Start)
      return generateNeighbour(G, currSchedule, tabuList, resources);
    numTentativas++;
  } while(numTentativas < 100 && !isValidSchedule(G, modifiedScheduleAux, task1, task2, task1Start, task2Start, resources));

  cout << task1 << "  " << task2 << endl;

  for(int i=0; i<G->totalDuration(); i++) {
    cout << modifiedSchedule[task1 - 1][i] << " ";
  }
  cout << endl;

  for(int i=0; i<G->totalDuration(); i++) {
    cout << modifiedSchedule[task2 - 1][i] << " ";
  }
  cout << endl;

  for(int i=0; i<G->totalDuration(); i++) {
    cout << modifiedScheduleAux[task1 - 1][i] << " ";
  }
  cout << endl;

  for(int i=0; i<G->totalDuration(); i++) {
    cout << modifiedScheduleAux[task2 - 1][i] << " ";
  }
  cout << endl;

  return modifyScheduleRepresentation(G, modifiedScheduleAux, 1);

  if (numTentativas < 100)
    tabuList.push_back(make_pair(task1, task2));
  modifiedSchedule = (numTentativas == 100 ? modifyScheduleRepresentation(G, modifiedSchedule, 1) : modifyScheduleRepresentation(G, modifiedScheduleAux, 1));

  modifiedSchedule.erase(std::remove_if(modifiedSchedule.begin(), modifiedSchedule.end(), [](std::vector<int>& arr) {
    return arr.empty();
  }), modifiedSchedule.end());

  return modifiedSchedule;
}

vector<vector<int>> tabuSearch(RCPSP<int>* G, vector<int> resources, int maxIter) {
  vector<vector<int>> currSchedule = scheduleTasks(G, resources);
  vector<vector<int>> bestSchedule = currSchedule;

  vector<pair<int,int>> tabuList;
  for (int i = 0; i < maxIter; i++) {
    vector<vector<int>> currSchedule = generateNeighbour(G, currSchedule, tabuList, resources);
    cout << "ENTROU" << endl;
    //return neighbourSchedule;
    //if (neighbourSchedule.size() <= currSchedule.size()) {
    //  currSchedule = neighbourSchedule;
      if (currSchedule.size() < bestSchedule.size()) {

          bestSchedule = currSchedule;
          //return bestSchedule;
      }
    //}
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

        // cout << G.size() << endl;

        microseconds durationScheduleTasks(0);
        auto startScheduleTasks = high_resolution_clock::now();

        vector<vector<int>> S = tabuSearch(
            &G, 
            resourceAvailabilities,
            5
          );

        auto stopScheduleTasks = high_resolution_clock::now();
        durationScheduleTasks = duration_cast<microseconds>(stopScheduleTasks - startScheduleTasks);

        vector<vector<int>> schedule = scheduleTasks(&G, resourceAvailabilities);

     string fileName = argv[1];
     std::replace( fileName.begin(), fileName.end(), '/', '-');
     string fileFolder = "log-files";
     auto arg = fileFolder + "/" + fileName + ".log";
     cout << arg << endl;

     std::ofstream file(arg);

        cout << "Makespan: " << schedule.size() << "   " << S.size() << endl;
        file << "Makespan: " << S.size() << endl;

        cout << "Time: " << durationScheduleTasks.count() << " microseconds" << endl;
        file << "Time: " << durationScheduleTasks.count() << " microseconds" << endl;

        cout << "Task schedule considering resource constraints and precedence relations:" << endl;
        file << "Task schedule considering resource constraints and precedence relations:" << endl;

        for (auto i = 0; i < schedule.size(); i++) {
            cout << "Running tasks [numPeriod=" << i + 1 << "]: {";
            for (auto j = 0; j < schedule[i].size(); j++) {
              if (j == schedule[i].size()-1) {
                cout << schedule[i][j];
                file << schedule[i][j];
                break;
              }
              cout << schedule[i][j] << ", ";
            }
            cout << "}" << endl;
        }

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
