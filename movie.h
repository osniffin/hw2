#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include <string>
#include "product.h"


class Movie : public Product {
public:
  Movie(const std::string &name, double price, int qty, const std::string &genre, const std::string &rating);
  virtual ~Movie();
  
  //virtual void =0 below 
  std::set<std::string> keywords() const;
  // returns the appropriate keywords to index the product 
  std::string displayString() const;
  //create a strong that contains the product info
  virtual void dump(std::ostream& os) const;

  double getPrice() const;
  std::string getName() const;
  int getQty() const;
  void subtractQty(int num);
  std::string getGenre() const;
  std::string getRating() const;

    
private:
    std::string genre_;
    std::string rating_;
};

#endif