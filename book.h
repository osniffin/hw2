#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include <string>
#include "product.h"


class Book : public Product {
public:
  Book(const std::string &name, double price, int qty, const std::string &isbn, const std::string &author);
  virtual ~Book();
  
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
  std::string getIsbn() const;
  std::string getAuthor() const;
  

    
private:
    std::string isbn_;
    std::string author_;
};

#endif