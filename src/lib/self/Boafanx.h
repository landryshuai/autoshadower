// last modified 

#pragma once

#include <string>
#include "../helper/Webpage.h"
#include "Certificate.h"

using std::string;


class Boafanx: public Webpage
{
    public:
        Boafanx (Certificate::Mode mode, const string& url_test, const string& savas_path);
        virtual ~Boafanx ();

    private:
        static const string boafanx_url;
};

