// last modified 

#pragma once

#include <string>
#include "../helper/Webpage.h"
#include "Certificate.h"

using std::string;


class Efmoe: public Webpage
{
    public:
        Efmoe (Certificate::Mode mode, const string& url_test, const string& savas_path);
        virtual ~Efmoe ();

    private:
        static const string efmoe_url;
};

