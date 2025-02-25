#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"


using namespace std;

Clothing::Clothing(const std::string &name, double price, int qty, const std::string &size, const std::string &brand): Product("clothing", name, price, qty), size_(size), brand_(brand) 
{

}


Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const 
{
  std::set<std::string> keywords = parseStringToWords(name_);
  //get keywords from the brand
  std::set<std::string> brandKeywords = parseStringToWords(brand_);
  //combine brand and product name
  for(const std::string &word : brandKeywords){
    keywords.insert(word);
  }
  return keywords;

}


double Clothing::getPrice() const
{
    return price_;
}

std::string Clothing::getName() const
{
    return name_;
}

void Clothing::subtractQty(int num)
{
    qty_ -= num;
}

int Clothing::getQty() const
{
    return qty_;
}

std::string Clothing::getSize() const
{
   return size_;
}
std::string Clothing::getBrand() const
{
    return brand_;
}


void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ <<"\n" << brand_ <<"\n";
}

std::string Clothing::displayString() const
{
    std::ostringstream s;
    s<< getName()<<"\n"
    <<"Size: "<< size_ << " Brand: " << brand_<<"\n"
    << std::fixed << std::setprecision(2)<<price_<<" "<<qty_<<" left."<<"\n";
    std::string clothingInfo = s.str();
    return clothingInfo;
}


