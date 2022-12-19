# 36C-3
## Third project
### Overview & Learning Objectives
In this program you will implement a priority queue with an underlying binary
heap implementation. There are multiple objectives of this assignment:
1. strengthen your knowledge of JSON,
2. strengthen your understanding of automated testing,
3. understand and implement a binary heap,
4. introduce greedy algorithms using a toy application (Volleyball team se-
lection).
This program consists of three parts:
1. creating a priority queue with an underlying binary heap implementation
(you will complete the files priorityqueue.cpp and priorityqueue.h),
2. build a binary heap given a sequence of instructions (you will complete
the file buildheap.cxx),
3. use your priority queue to construct a greedy algorithm to pick "fair" 2-
person teams from a list of Volleyball players.

### Build Teams
The contents of BuildExample.json, an example of a JSON file of operations,
is as follows:
```
{
  "Op01": {
    "key": 3019,
    "operation": "insert"
  },
  "Op02": {
    "key": 1500,
    "operation": "insert"
  },
  "Op03": {
    "key": 1334,
    "operation": "insert"
  },
  "Op04": {
    "key": 4119,
    "operation": "insert"
  },
  "Op05": {
    "operation": "removeMin"
  },
  "Op06": {
    "key": 2199,
    "operation": "insert"
  },
  "Op07": {
    "operation": "removeMin"
  },
  "Op08": {
    "operation": "removeMin"
  },
  "Op09": {
    "key": 4180,
    "operation": "insert"
  },
  "Op10": {
    "key": 4586,
    "operation": "insert"
  },
  "metadata": {
    "maxHeapSize": 4,
    "numOperations": 10
  }
}
```
After running build heap, my output using std::cout << jsonObj.dump(2)
on the result is:
```
{
  "1": {
    "key": 3019.0,
    "leftChild": "2",
    "rightChild": "3",
    "value": [0, 0]
  },
  "2": {
    "key": 4119.0,
    "leftChild": "4",
    "parent": "1",
    "value": [0, 0]
  },
  "3": {
    "key": 4180.0,
    "parent": "1",
    "value": [0, 0]
  },
  "4": {
    "key": 4586.0,
    "parent": "2",
    "value": [0, 0]
  },
  "metadata": {
    "maxHeapSize": 4,
    "numOperations": 10,
    "size": 4
  }
}
```

### Create Teams

Use your priority queue to implement the above greedy algorithm

1. Pick a 2-person team with a win percentage as close to 50% as possible.
2. For each of the two players in the 2-person team picked in part 1, remove
all data of other 2-person teams that contain at least one of these players.
That is, every player must be assigned to exactly one team.
3. Go to step 1 if fewer than n 2-person teams have been created.

Your input files will be look like this, which is the contents of CreateTeamsExample.json:
```
{
  "metadata": {
    "numPlayers": 4
  },
  "teamStats": [
    {
      "playerOne": 0,
      "playerTwo": 1,
      "winPercentage": 55.11
    },
    {
      "playerOne": 0,
      "playerTwo": 2,
      "winPercentage": 29.748
    },
    {
      "playerOne": 0,
      "playerTwo": 3,
      "winPercentage": 14.872
    },
    {
      "playerOne": 1,
      "playerTwo": 2,
      "winPercentage": 53.724
    },
    {
      "playerOne": 1,
      "playerTwo": 3,
      "winPercentage": 95.86
    },
    {
      "playerOne": 2,
      "playerTwo": 3,
      "winPercentage": 65.498
    }
  ]
}
```

The final teams are stored in a JSON object and printed to stdout:
```
{
  "teams": [
    [1, 2],
    [0, 3]
  ]
}
```

