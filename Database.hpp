//
//  Data.hpp
//  OHFinal
//
//  Created by 惠鸥 on 11/27/16.
//  Copyright © 2016 XO. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp
#include <vector>
#include <string>
//By using singleton, we set the only way to access files
class Database
{
private:
    static Database *data_ptr;
    std::string FileName;
    Database(std::string FileName_ = "");
    
public:
    void setFileName(const std::string& FileName_);
    bool readFile(std::vector<std::string>& _File);
    static Database *instance()
    {
        if(!data_ptr)
            data_ptr = new Database;
        return data_ptr;
    }
    
};

inline void Database::setFileName(const std::string& FileName_)
{
    FileName = FileName_;
}



#endif /* Data_hpp */
