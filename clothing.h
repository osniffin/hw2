#ifndef CLOTHING_H
#define CLOTHING_H

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include <string>
#include "product.h"


class Clothing : public Product {
public:
  Clothing(const std::string &name, double price, int qty, const std::string &size, const std::string &brand);
  virtual ~Clothing();
  
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
  std::string getSize() const;
  std::string getBrand() const;

    
private:
    std::string size_;
    std::string brand_;
};

#endif