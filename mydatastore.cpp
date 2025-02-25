#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() 
{
  for(size_t i=0; i<products.size(); ++i) 
  {
    delete products[i];
  }
  for(size_t i=0; i<users.size(); ++i) 
  {
    delete users[i];
  }
}

void MyDataStore::addProduct(Product* p)
{
  // print invalid request if inproper input
  if(p==nullptr){
    std::cout<< "Invalid request"<<std::endl;
    return;
  }
  products.push_back(p);
  //add to map
  std::set<std::string> k = p->keywords();

  for(std::set<std::string>::iterator it=k.begin(); it != k.end(); ++it)
  {
    keywordToProductMap[*it].push_back(p);
  }
}


void MyDataStore::addUser(User* u) 
{
  if(u==nullptr){
    std::cout<< "Invalid request"<<std::endl;
    return;
  }

  users.push_back(u);
}


std::vector<Product*>MyDataStore::search(std::vector<std::string>& terms, int type)
{
  if(terms.empty())//No keyword provided
  {
    std::cout<<"Please provide a search term"<<std::endl;
    return std::vector<Product*>();
  }
  
  std::set<Product*> searchResults; // products found during the search
  std::vector<std::set<Product*>> matches;
  //dumpKeywordMap();

  for(size_t i=0; i<terms.size();i++)
  {
    std::string term = convToLower(terms[i]);
    
    //cout<<term<<endl;

    if(keywordToProductMap.find(term)!=keywordToProductMap.end())
    {
      std::set<Product*> productSet(keywordToProductMap[term].begin(), keywordToProductMap[term].end());
      matches.push_back(productSet);   
    }
    else
    {
      if(type==0)
      {
        return std::vector<Product*>();
      }
    }
  }
  //cout<<matches.size()<<endl;
  if(matches.empty())
  {
    searchResults.clear();
    return std::vector<Product*>();
  }
  if(type==0)
  {
    searchResults = matches[0];

    for(size_t i=1; i<matches.size();i++)
    {
      searchResults = setIntersection(searchResults,matches[i]);
    }

  }
  else if(type==1)
  {
    searchResults = matches[0];
    for(size_t i=1; i<matches.size();i++)
    {
      searchResults = setUnion(searchResults,matches[i]);
    }
  }

  std::vector<Product*> foundProducts(searchResults.begin(), searchResults.end()); //list of products with found matches to be returned
  
  return foundProducts;
}


void MyDataStore::dump(std::ostream& ofile)
{

  ofile << "<products>" << std::endl;
  for(size_t i=0;i<products.size();i++)
  {
    products[i]->dump(ofile);
  }
  ofile << "</products>" << std::endl;

  ofile << "<users>" << std::endl;
  for(size_t i = 0; i < users.size(); i++)
  {
    users[i]->dump(ofile);
  }
  ofile << "</users>" << std::endl;
  
}


void MyDataStore::buyCart(const std::string& username)
{
  std::string lowerCaseUsername = convToLower(username);
  User* selectedUser = nullptr;
  for (User* u : users){
    if(convToLower(u->getName()) == lowerCaseUsername){
      selectedUser=u;
      break;
    }
  }

  if(!selectedUser){
    std::cout<<"Invalid username"<< std::endl;
    return;
  }
 
  if(carts.find(selectedUser) == carts.end()) 
  {
    std::cout << "Cart is empty" << std::endl;
    return;
  } 

  std::vector<Product*>& cart = carts[selectedUser] ;
  std::vector<Product*> leftoverCart;

  for(std::vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it)
  {
    Product* p = *it;
    double balance = selectedUser-> getBalance();
    int stock = p-> getQty();
    double itemPrice = p->getPrice();
    
    //cout << "Item Price Test: "<< itemPrice<< endl << "balance: "<<balance;

    if(itemPrice <= balance && stock>0)
    {
     // cout << "Test if start: Balance-"<<balance<<"Stock: "<<stock <<endl;
      //decrese stock
      p->subtractQty(1); 
      // decrease money
      selectedUser->deductAmount(itemPrice);
      //remove item from cart 
      //cout << "Test if end: Balance-"<<balance<<"Stock: "<<stock <<endl;
    }
    else{
      leftoverCart.push_back(p);
    }
  }
  carts[selectedUser]=leftoverCart;  
}


void MyDataStore::viewCart(const std::string& username)
{
  std::string lowerCaseUsername = convToLower(username);
  User* selectedUser = nullptr;

  for (User* u : users){
    if(convToLower(u->getName()) == lowerCaseUsername){
      selectedUser=u;
      break;
    }
  }
  if(!selectedUser){
    std::cout<<"Invalid username"<< std::endl;
    return;
  }

  std::vector<Product*>& userCart = carts[selectedUser];
  if(userCart.empty())
  {
    std::cout <<"Cart is empty"<< std::endl;
    return;
  }

  std::cout<< username <<"'s Cart:"<< std::endl;

  for(size_t i=0;i<userCart.size();i++){
    std::cout<<i+1<<". " << userCart[i]->displayString()<<"\n";
  }
  //dumpCartMap();
}


void MyDataStore::addToCart(const std::string& username, int indexNum, const std::vector<Product*>& hits)
{ 
  if(hits.empty())
  {
    std::cout<<"Error: Empty Cart"<<std::endl;
    return;
  }

  std::string lowerCaseUsername = convToLower(username);
  User* selectedUser = nullptr;

  for(std::vector<User*>::iterator it = users.begin(); it != users.end(); ++it)
  {
    User* u=*it;
    if(lowerCaseUsername==convToLower(u->getName()))
    {
      selectedUser = u;
      break;
    }
  }

  if(!selectedUser){
    std::cout<<"Invalid request"<< std::endl;
    return;
  }

  if(indexNum<1||indexNum>static_cast<int>(hits.size()))
  {
    std::cout<< "Invalid request"<<std::endl;
    return;
  }
  std::vector<Product*>& userCart = carts[selectedUser];
  Product* selectedProduct = hits[indexNum - 1];

  userCart.push_back(selectedProduct);

  std::cout << "Product added to cart." << "\n";
  //dumpCartMap();
}


void MyDataStore::dumpCartMap()
{
  std::map<User*, std::vector<Product*>>::iterator it;
  for(it=carts.begin();it!=carts.end();it++)
  {
    std::string key = it->first->getName();
    std::vector<Product*> p = it->second;

    std::cout<<key<<": "<< p.size();
    std::cout<<std::endl;
  }
  std::cout<<std::endl;

}
