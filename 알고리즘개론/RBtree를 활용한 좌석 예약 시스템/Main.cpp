#include "Constants.h"
#include "Movie.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace Constants;

//Movie list
std::vector<std::vector<Movie>> movie_list = {
  // Sunday Movies
  {
      Movie(1, "Gravity", 0, 0),
      Movie(2, "Matrix", 0, 1),
      Movie(3, "Jaws", 0, 2),
      Movie(4, "Big", 0, 3),
      Movie(5, "Up", 0, 4)
  },
  // Monday Movies
  {
      Movie(6, "Gravity", 1, 0),
      Movie(7, "Se7en", 1, 1),
      Movie(8, "Jaws", 1, 2),
      Movie(9, "Heat", 1, 3),
      Movie(10, "Memento", 1, 4)
  },
  // Tuesday Movies
  {
      Movie(11, "Gravity", 2, 0),
      Movie(12, "Arrival", 2, 1),
      Movie(13, "Jaws", 2, 2),
      Movie(14, "Looper", 2, 3),
      Movie(15, "Moon", 2, 4)
  },
  // Wednesday Movies
  {
      Movie(16, "Star Wars", 3, 0),
      Movie(17, "Babe", 3, 1),
      Movie(18, "Aladdin", 3, 2),
      Movie(19, "Coco", 3, 3),
      Movie(20, "Shrek", 3, 4)
  },
  // Thursday Movies
  {
      Movie(21, "Psycho", 4, 0),
      Movie(22, "Alien", 4, 1),
      Movie(23, "Fargo", 4, 2),
      Movie(24, "Babe", 4, 3),
      Movie(25, "Crash", 4, 4)
  },
  // Friday Movies
  {
      Movie(26, "Juno", 5, 0),
      Movie(27, "Her", 5, 1),
      Movie(28, "Drive", 5, 2),
      Movie(29, "Alien", 5, 3),
      Movie(30, "Babe", 5, 4)
  },
  // Saturday Movies
  {
      Movie(31, "Joker", 6, 0),
      Movie(32, "Logan", 6, 1),
      Movie(33, "Rush", 6, 2),
      Movie(34, "Bolt", 6, 3),
      Movie(35, "Alien", 6, 4)
  }
};

//Reservation
//Choose seat number
void Reservation(Movie& movie) {
  //
  //First choose day
  //
  cout << "0 : Quit" << endl;
  cout << "Choose number of seat you want to reserve : " << endl;
  string user_input;

  while (user_input != "0") {
    cin >> user_input;
    int reservation_id = movie.Reservation(user_input);
    if (reservation_id !=-1) {
      cout << "Reservation Complete!" << endl;
      cout << "Reservation ID: " << reservation_id << endl;
      cout << "Reserved Movie : " << movie.movie_name << endl;
      cout << "Movie Day : " << day_of_week[movie.day] << endl;
      cout << "Movie Start Time : " << staring_time[movie.start_time] << endl;
      cout << "Seat number : " << user_input << endl;
      movie.PrintSits();
      break;
    }
    else {
      cout << "Error Invalid Number. Try again :" << endl;
    }
  }
}

//display day and time of movie
//user input number to choose
void ChooseMovie() {
  string user_input;

  //
  //First choose day
  //
  cout << "Choose number of day you want to check : " << endl;

  for (int i = 0; i < 7; i++) {
    cout << i + 1 << " : Check " << day_of_week[i] << " movies" << endl;
  }
  cout << "0 : Quit" << endl;

  while (user_input != "0") {
    cin >> user_input;
    try {
      int day_number = stoi(user_input);

      if (day_number >= 1 && day_number <= 7) {
        //
        // Display movies for the chosen day
        //
        cout << "Movies for " << day_of_week[day_number - 1] << endl;
        auto& movies = movie_list[day_number - 1];
        int i = 1;
        for (const Movie movie : movies) {
          cout << i << ": " << staring_time[movie.start_time] << ": " << movie.movie_name << endl;
          i++;
        }
        cout << "0 : Quit" << endl;

        cout << "Input number of the movie you want to reserve" << endl;
        while (user_input != "0") {
          cin >> user_input;

          try {
            int chosen_movie_number = stoi(user_input);
            if (chosen_movie_number >= 1 && chosen_movie_number <= 5) {
              Movie& movie = movies[chosen_movie_number - 1];
              movie.PrintSits();
              Reservation(movie);
              break;
            }
            else {
              if (day_number != 0)
                cout << "Error Invalid Number. Try again :" << endl;
            }
          }
          catch (const std::exception) {
            cout << "Error Invalid input. Try again :"  << endl;
          }
        }

        break;
      }
      else {
        if(day_number !=0)
          cout << "Error Invalid Number. Try again :" << endl;
      }
    }
    catch (const std::exception) {
      cout << "Error Invalid input. Try again :" << endl;
    }
  }
}

void Cancelation() {

  cout << "0 : Quit" << endl;
  cout << "Enter reservation id you want to cancel : " << endl;

  string user_input;
  while (user_input != "0") {
    cin >> user_input;
    if (user_input == "0") break;
    try {
      int reservation_id = stoi(user_input);
      int movie_id_get = reservation_id % 100;
      bool found = false;
      for (auto& movies : movie_list) {
        for (Movie movie : movies) {
          if (movie.movie_id == movie_id_get) {
            if (movie.CancelReservation(reservation_id)) {
              movie.PrintSits();
              found = true;
              break;
            }
          }
        }
      }
      if (found) break;
      else cout << "Error Invalid input. Try again :" << endl;
    }
    catch (const std::exception) {
      cout << "Error Invalid input. Try again :" << endl;
    }
  }
}
int main() {

  string user_input;
  while (user_input!="0") {
    cout << "Choose Activity :" << endl;
    cout << "1 : Movie Reservation " << endl;
    cout << "2 : Cancel Reservation" << endl;
    cout << "0 : Quit" << endl;
    cin >> user_input;

    if (user_input == "1") {
      ChooseMovie();
    }
    else if (user_input == "2") {
      Cancelation();
    }
    else if (user_input == "0") {
      break;
    }
  }

  return 0;
}
