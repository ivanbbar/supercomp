#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <bitset>

using namespace std;

struct Movie {
    int id;
    int start_time;
    int end_time;
    int category;
};

bool compare_movie(Movie a, Movie b) {
    return a.end_time > b.end_time;
}


int main() {
    int n, m;
    cin >> n >> m;

    vector<int> max_filmes(m);
    for (int i = 0; i < m; i++) {
        cin >> max_filmes[i];
    }

    vector<Movie> movies;

    for (int i = 0; i < n; i++) {
        int start_time, end_time, category;
        cin >> start_time >> end_time >> category;

        if (start_time > end_time) {
            if (end_time == 0) {
                end_time = 24;
            } else if (start_time == -1 || end_time == -1) {
                continue;
            } else {
                continue;
            }
        }

        Movie movie;
        movie.id = i + 1;
        movie.start_time = start_time;
        movie.end_time = end_time;
        movie.category = category;

        movies.push_back(movie);
    }

    sort(movies.begin(), movies.end(), compare_movie);

    int dp[n+1][m+1] = {0};
    
    int i,j;
    for (i=1; i <= n; i++) { 
        for (j =1; j<= m; j++) {
            dp[i][j]=0;
        }
    }

    for (j =1; j<= m; j++) {
        dp[0][j]=max_filmes[j];
    }

    for (i=1; i <= n; i++) { 
        for (j =1; j<= m; j++) {
            if (movies[i].category != j) {
                dp[i][j] = dp[i-1][j];
            }
            else {
                int last = i-1;
                while (last >= 0 && movies[last].end_time > movies[i].start_time) {
                    last -=1;
                }

                int max_count = 0;
                int k;
                for (k=0; k < min(dp[last][j-1], movies[i].end_time - movies[i].start_time - 1); k++) { 
                    max_count = max(max_count, dp[last][j-1-k] + k + 1);
                }
                dp[i][j] = max(dp[i-1][j], max_count);
            }
        }
    }

    for(int row = 1; row <= n; row++)
    {
        for (int column = 1; column <= m; column++)
        {
            cout<< dp[row][column];
        }

        cout<<endl;
    }

    return 0;
}