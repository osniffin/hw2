#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <deque>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>

#include "datastore.h"
#include "util.h"
#include "product.h"
#include "user.h"



class MyDataStore: public DataStore{
public:
    MyDataStore();
    virtual ~MyDataStore();
    virtual void addProduct(Product* p);
    virtual void addUser(User* u);
    
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);
    
    virtual void dump(std::ostream& ofile);

    void buyCart(const std::string& username);
    void viewCart(const std::string& username);
    void addToCart(const std::string& username, int productNum, const std::vector<Product*>& hits);

    void dumpCartMap();
    
    //use displayProducts(vector<Product*>& hits) to display
    
private:
    //products, users, carts
    std::vector<Product*> products; 
    
    std::vector<User*> users; 

    std::map<User*, std::vector<Product*>> carts;  

    std::map<std::string, std::vector<Product*>> keywordToProductMap;
};

#endif
