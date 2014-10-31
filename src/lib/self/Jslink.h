// last modified 

#pragma once

#include <string>
#include "../helper/Webpage.h"
#include "Certificate.h"

using std::string;


class Jslink : public Webpage
{
    public:
        Jslink (Certificate::Mode mode, const string& url_test, const string& savas_path);
        virtual ~Jslink ();

    private:
        static const string jslink_url;
};

