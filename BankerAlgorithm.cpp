#include <iostream>
using namespace std;

int main()
{
    const int n = 5, // Number of processes
              m = 3; // Number of resources      

    //Allocation matrix
                           // A  B  C
    int allocation[5][3] = {{ 0, 1, 0 },  // p0 
                            { 2, 0, 0 },  // p1
                            { 3, 0, 2 },  // p2
                            { 2, 1, 1 },  // p3
                            { 0, 0, 2 }}; // p4
    //Max matrix
                    // A  B  C
    int max[5][3] = {{ 7, 5, 3 },  // p0 
                     { 3, 2, 2 },  // p1
                     { 9, 0, 2 },  // p2
                     { 2, 2, 2 },  // p3
                     { 4, 3, 3 }}; // p4
    //Need matrix
    int need[n][m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    //Available resources
                      // A  B  C
    int available[3] = { 3, 3, 2 }; 

    int seq[n];

    int index = 0;

    int remaining = n;

    bool taken[n];

    for (int i = 0; i < n; i++) 
    {
        taken[i] = false;
    }

    for (int k = 0; k < remaining; k++)  
    {
        for (int i = 0; i < n; i++)  
        {
            if (!taken[i])
            {
                bool process_safe = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        process_safe = false;
                        break;
                    }
                }
              
                if (process_safe)
                { 
                    seq[index] = i;

                    for (int x = 0; x < m; x++)
                    {
                        available[x] += allocation[i][x];
                    }

                    index++;
                    remaining--;
                    taken[i] = true;
                }
            }
        }
    }

    bool is_safe = true;

    //Check if sequence SAFE
    for (int i = 0; i < n; i++)
    {
        if (!taken[i])
        {
            is_safe = false;
            cout << "NOT SAFE Sequence";
            break;
        }
    }

    if (is_safe)
    {
        cout << "SAFE Sequence :\n";

        for (int i = 0; i < n; i++)
        {
            cout << " p" << seq[i];

            if (i != n - 1)
                cout << " ,";
        }       
    }

    cout << endl;

    return 0;
}
