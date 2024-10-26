#include "Movie.h"
#include <cstdlib>

Movie::Movie(int id, std::string name, int day_, int startTime) 
  : movie_id(id), movie_name(std::move(name)), day(day_), start_time(startTime),
  seats{} {
  int i = 0;
  srand(1);
  while (i < 60) {
    i++;
    int row = rand() % 10;
    int col = rand() % 20;
    while (seats[row][col]) {
      row = rand() % 10;
      col = rand() % 20;
    }
    string seat_number = char('A' + row) + std::to_string(col + 1);
    Node* n = new Node(movie_id, movie_name, start_time, day, seat_number);
    rbTree.insert(n);
    seats[row][col] = true;
  }
}

Movie::~Movie() {

}

void Movie::PrintSits() {
  char row = 'A';
  std::cout << "----------------------------------------------------------------" << endl ;
  std::cout << "Movie Name : " << movie_name << endl << endl;

  //RbTree print
  rbTree.print();

  std::cout << endl;
  std::cout << "Movie seats : " << endl;
  //Movie seats print
  for (int i = 0; i < 10; i++) {

    for (int j = 0; j < 20; j++) {
      if (!seats[i][j]) {
        std::cout << '[' << row << j + 1 << "] ";
      }
      else {
        std::cout << "[XX] ";
      }
    }

    std::cout << std::endl;
    row += 1;
  }
  std::cout << "----------------------------------------------------------------" << endl;
}

int Movie::Reservation(std::string seat_number) {
  if (seat_number.length() < 2) return -1; // Minimum input length

  char row_char = seat_number[0];
  int row_index = row_char - 'A'; //Get row part
  if (row_index < 0 || row_index >= 10) return -1; // Check row bounds

  int col_index;
  try {
    col_index = std::stoi(seat_number.substr(1)) - 1; // Get column part
  }
  catch (const std::invalid_argument) {
    return -1; // Conversion failed
  }

  if (col_index < 0 || col_index >= 20) return -1; // Check column bounds

  // Now check the seat status
  if (seats[row_index][col_index]) {
    return -1; // Seat is already taken
  }
  else {// Reserve the seat
    seats[row_index][col_index] = true; 
    Node* newNode = new Node(movie_id, movie_name, start_time, day, seat_number);
    rbTree.insert(newNode);
    return newNode->reserve_id; // Successful reservation
  }
}
bool Movie::CancelReservation(int reserve_id) {
  string seat_number = rbTree.remove(reserve_id);
  if (seat_number !="Q") {
    char row_char = seat_number[0];
    int row_index = row_char - 'A'; //Get row part
    int col_index = std::stoi(seat_number.substr(1)) - 1; // Get column part
    seats[row_index][col_index] = false;
    return true;
  }
  else {
    return false;
  }
}