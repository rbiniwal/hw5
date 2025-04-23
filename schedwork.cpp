#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    sched.resize(numDays);
    std::vector<size_t> shiftsAssigned(numWorkers, 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsAssigned, 0);




}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsAssigned,
    size_t day
)
{
    if (day == avail.size()) 
    {
        return true;
    }
    return assignDayWorkers(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day, 0);
}

bool assignDayWorkers(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsAssigned,
    size_t day,
    size_t workerIndex
)
{
    if (sched[day].size() == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day + 1);
    }

    size_t numWorkers = avail[0].size();

    for (Worker_T w = workerIndex; w < numWorkers; ++w) 
    {
        if (avail[day][w] && shiftsAssigned[w] < maxShifts &&
            find(sched[day].begin(), sched[day].end(), w) == sched[day].end()) 
        {
            sched[day].push_back(w);
            shiftsAssigned[w]++;
            if (assignDayWorkers(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day, 0)) 
            {
                return true;
            }
            sched[day].pop_back();
            shiftsAssigned[w]--;
        }
    }
    return false;
}

