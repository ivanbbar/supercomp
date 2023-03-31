#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Movie {
    int id;
    int start_time;
    int end_time;
    int category;
};

struct Category {
    int id;
    int num_movies;
};

struct Marathon {
    vector<int> times;
    vector<int> movies;
};

int get_movie_length(const Movie& movie) {
    return movie.end_time - movie.start_time;
}

bool compare_movies(const Movie& movie1, const Movie& movie2) {
    return movie1.end_time < movie2.end_time;
}

int main() {
    int N, M;
    cin >> N >> M;

    // Parse the movies
    vector<Movie> movies(N);
    for (int i = 0; i < N; i++) {
        cin >> movies[i].start_time >> movies[i].end_time >> movies[i].category;
        movies[i].id = i;
    }

    // Parse the maximum number of movies per category
    vector<int> max_movies(M);
    for (int i = 0; i < M; i++) {
        cin >> max_movies[i];
    }

    // Sort the movies by increasing end time
    sort(movies.begin(), movies.end(), compare_movies);

    // Initialize the number of watched movies to zero for each category
    vector<Category> categories(M);
    for (int i = 0; i < M; i++) {
        categories[i].id = i;
        categories[i].num_movies = 0;
    }

    // Select the movies
    int num_watched = 0;
    Marathon marathon;
    marathon.times.push_back(0);
    for (const auto& movie : movies) {
        // Check if there are available spots in the category
        if (categories[movie.category - 1].num_movies < max_movies[movie.category - 1]) {
            // Check if the movie can be watched without overlapping with the marathon
            bool can_watch = true;
            for (int i = 0; i < marathon.movies.size(); i++) {
                if (movie.start_time < marathon.times[i + 1] && movie.end_time > marathon.times[i]) {
                    can_watch = false;
                    break;
                }
            }
            if (can_watch) {
                // Watch the movie and update the number of watched movies and the marathon
                categories[movie.category - 1].num_movies++;
                marathon.movies.push_back(movie.id);
                marathon.times.push_back(movie.end_time);
                num_watched++;
            }
        }
    }

    // Print the output
    cout << num_watched << endl;

    return 0;
}

