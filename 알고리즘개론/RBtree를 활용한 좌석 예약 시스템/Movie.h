#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>
#include <memory>

#include "RbTree.h"

struct Movie {
  int movie_id;
  std::string movie_name;
  const int day; //0~6
  const int start_time; //0~5
  RbTree rbTree;
  bool seats[10][20];                  

  // Constructor & Destructor
  Movie(int id, std::string name, int day, int startTime);
  ~Movie();

  //Print seats
  //A1 ~ A20 ... J1 ~ J20
  void PrintSits();

  //Reservation
  int Reservation(std::string seat_number);
  bool CancelReservation(int reserve_id);
};

#endif
