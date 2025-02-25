#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string &name, double price, int qty, const std::string &isbn, const std::string &author): Product("book", name, price, qty), isbn_(isbn), author_(author) 
{

}


Book::~Book()
{
  

}

std::set<std::string> Book::keywords() const 
{
  std::set<std::string> keywords1 = parseStringToWords(name_);
  std::set<std::string> authorKeywords = parseStringToWords(author_);

  for(const std::string &word : authorKeywords){
    keywords1.insert(word);
  }

  //insert ISBN
  keywords1.insert(isbn_);

  return keywords1;
}

double Book::getPrice() const
{
    return price_;
}

std::string Book::getName() const
{
    return name_;
}

void Book::subtractQty(int num)
{
    qty_ -= num;
}

int Book::getQty() const
{
    return qty_;
}

std::string Book::getIsbn() const
{
   return isbn_;
}
std::string Book::getAuthor() const
{
    return author_;
}




void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) <<  price_ << "\n" << qty_ << "\n" << isbn_ <<"\n" << author_ <<"\n";
}

std::string Book::displayString() const
{
    std::ostringstream s;
    /*
    s<< getName()<< std::endl 
    <<"Author: "<< getAuthor() << " ISBN: " << getIsbn()<< std::endl
    <<getPrice()<<" "<<getQty()<<" left."<<std::endl;
    std::string bookInfo = s.str();
    
    std::string q = std::to_string(getQty());

    s<<getName()<< std::endl 
    <<"Author: "<< getAuthor() << " ISBN: " << getIsbn()<< std::endl
    <<getPrice()<<" "<< q <<" left."<<std::endl;
    //<<"stock: " << getQty()<<","<<std::endl
   // <<"price: "<<getPrice()<<std::endl;
   */
    s<<name_<< "\n"<<"Author: "<< author_<<" ISBN: " << isbn_<<"\n"
    << std::fixed << std::setprecision(2)<<price_<<" "<< qty_<< " left."<<"\n";
    
    std::string bookInfo = s.str();


    
    return bookInfo;
}



