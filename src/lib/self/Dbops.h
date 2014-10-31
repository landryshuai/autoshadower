// last modified 

#pragma once

#include <string>
#include "../helper/Webpage.h"
#include "Certificate.h"

using std::string;


class Dbops: public Webpage
{
    public:
        Dbops (Certificate::Mode mode, const string& url_test, const string& savas_path);
        virtual ~Dbops ();

    private:
        static const string dbops_url;
};

