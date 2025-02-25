#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"


using namespace std;

Movie::Movie(const std::string &name, double price, int qty, const std::string &genre, const std::string &rating): Product("movie", name, price, qty), genre_(genre), rating_(rating) 
{

}


Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const 
{
  std::set<std::string> keywords = parseStringToWords(name_);
  //get genre as keyword
  keywords.insert(convToLower(name_));
  keywords.insert(convToLower(genre_));
  return keywords;
}


double Movie::getPrice() const
{
    return price_;
}

std::string Movie::getName() const
{
    return name_;
}

void Movie::subtractQty(int num)
{
    qty_ -= num;
}

int Movie::getQty() const
{
    return qty_;
}

std::string Movie::getGenre() const
{
   return genre_;
}
std::string Movie::getRating() const
{
    return rating_;
}



void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ <<"\n" << rating_ <<"\n";
}

std::string Movie::displayString() const
{
    std::ostringstream s;
    s<< getName()<<"\n" 
    <<"Genre: "<< genre_ << " Rating: " << rating_<<"\n"
    << std::fixed << std::setprecision(2)<<price_<<" "<<qty_<<" left."<<"\n";
    std::string movieInfo = s.str();
    return movieInfo;
}

