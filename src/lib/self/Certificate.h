// last modified 

#pragma once
#include <string>
#include "../helper/Webpage.h"

using std::string;

class Certificate 
{
    public:
        enum Mode {available, region, avarspeed, all};

    public:
        Certificate ( Mode mode,
                      const string& url_test,
                      const string& server, 
                      const string& server_port,
                      const string& password,
                      const string& method = "aes-256-cfb",
                      const string& local_addr = "127.0.0.1",
                      const string& fast_open = "false",
                      const string& timeout = "512",
                      const string& workers = "1" );
        virtual ~Certificate ();
        
        bool isAvailable (void) const;
        const string& getRegion (void) const; 
        double getAvarSpeed (void) const; 
        
        bool saveas (const string& path) const;

    protected:
        bool checkAvailable_ (void) const;
        string checkRegion_ (void) const;
        double checkAvarSpeed_ (void) const;
        bool writeJsonFile_ (const string& filename) const;

    private:
        Mode mode_;
        const string url_test_;
        
        const string server_;
        const string server_port_;
        const string password_;
        const string method_;
        const string local_addr_;
        const string fast_open_;
        const string timeout_;
        const string workers_;
        string local_port_;
        
        bool b_avail_;
        double aver_speed_;
        string region_;
        
        pid_t pid_ss_;
        
        Webpage* p_webpage_test_;

    private:
        static unsigned valid_cnt_;
        static const unsigned local_port_start_;
};

