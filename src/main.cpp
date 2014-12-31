#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <sys/stat.h>
#include <sys/types.h>
#include "lib/self/Certificate.h"
#include "lib/self/Boafanx.h"
#include "lib/self/Itplayer.h"
#include "lib/self/Efmoe.h"
#include "lib/helper/Time.h"
#include "lib/helper/CmdlineOption.h"
#include "lib/helper/RichTxt.h"

using namespace std;


static const string g_softname(RichTxt::bold_on + "autoshadower" + RichTxt::bold_off);
static const string g_version("0.1.0");
static const string g_myemail("yangyangwithgnu@yeah.net");
static const string g_myemail_color(RichTxt::bold_on + RichTxt::foreground_green + g_myemail + RichTxt::reset_all);
static const string g_mywebspace("http://yangyangwithgnu.github.io/");
static const string g_mywebspace_color(RichTxt::bold_on + RichTxt::foreground_green + g_mywebspace + RichTxt::reset_all);


static void
showHelpInfo (void)
{
    cout << endl;
    cout << "  " << g_softname << " is so sweet, she will find many free shadowsocks accounts for you, do her best! "
         << RichTxt::bold_on << "but, first of all, your system has installed sslocal by yourself. " << RichTxt::bold_off
         << "you can get it from https://github.com/clowwindy/shadowsocks. " << endl
         << "  ok, now enjoy it. autoshadower is easy and simple to use. Usually, you can issue it as follow: " << endl
         << "  $ autoshadower" << endl
         << "or" << endl
         << "  $ autoshadower --mode all --path ~/downloads" << endl;

    cout << endl;
    cout << "  --help" << endl
         << "  ---------------" << endl
         << "  Show this help infomation what you are seeing. " << endl;

    cout << endl;
    cout << "  --version" << endl
         << "  ---------------" << endl
         << "  Show current version. " << endl;

    cout << endl;
    cout << "  --path" << endl
         << "  ---------------" << endl
         << "  Set the path to save SS certificate files. the rule of subdir is SS_certs@@mmddhhmmss, "
         << "the rule of shadowsocks certificate file is localport.json or localport-[avarspeed]-[region].json. " << endl
         << "  The default directory is home directory or C:\\ " << endl;

    cout << endl;
    cout << "  --mode" << endl
         << "  ---------------" << endl
         << "  Set the mode how to find SS certificate. there are four modes: " << endl
         << "    0) a (available). just find which SS certificate is available; " << endl
         << "    1) r (region). find which SS certificate is available, and the region of certificate out ip; " << endl
         << "    2) s (averspeed). find which SS certificate is available, and the average speed of certificate out ip; " << endl
         << "    3) all. included a, r, and s. " << endl
         << "  default a" << endl;

    cout << endl;
    cout << "  That's all. Any suggestions let me know by "
         << g_myemail_color
         << " or "
         << g_mywebspace_color
         << ", big thanks to you. " << endl << endl;
}

static void
showVersionInfo (void)
{
    cout << "autoshadower version " << g_version << endl
         << "email " << g_myemail << endl
         << "webspace " << g_mywebspace << endl << endl;
}


int
main (int argc, char* argv[])
{
    // parse command line options
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    CmdlineOption cmdline_options((unsigned)argc, argv);
    vector<string> cmdline_arguments_list;

    // --help, first high priority, ignore other options
    if (cmdline_options.hasOption("--help")) {
        showHelpInfo();
        return(EXIT_SUCCESS);
    }

    // --version, second high priority, ignore other options
    if (cmdline_options.hasOption("--version")) {
        showVersionInfo();
        return(EXIT_SUCCESS);
    }

    // 提示用户安装 sslocal
    cout << RichTxt::bold_on
         << "********************** !! IMPORTANCE !! **********************" << endl
         << "*********  please make sure *sslocal* is installed  **********" << endl
         << "********************** !! IMPORTANCE !! **********************" << endl
         << RichTxt::bold_off << endl;

    // --mode
    // >>>>>>>>>>>>>>>>>>
    Certificate::Mode mode = Certificate::available;
    string mode_argument("available");

    cmdline_arguments_list = cmdline_options.getArgumentsList("--mode");
    if (!cmdline_arguments_list.empty()) {
        const string& argument = cmdline_arguments_list[0];
        if ("a" == argument) {
            mode = Certificate::available;
            mode_argument = "available";
        } else if ("r" == argument) {
            mode = Certificate::region;
            mode_argument = "region";
        } else if ("s" == argument) {
            mode = Certificate::avarspeed;
            mode_argument = "avarspeed";
        } else if ("all" == argument) {
            mode = Certificate::all;
            mode_argument = "all";
        } else {
            cerr << "ERROR! --mode argument setting wrong! " << endl;
            return(EXIT_FAILURE);
        }
    }

    cout << "the mode to find SS certificate files \"" << RichTxt::bold_on << mode_argument << RichTxt::bold_off << "\"; " << endl;
    // <<<<<<<<<<<<<<<<<<

    // --path
    // >>>>>>>>>>>>>>>>>>
    string path;

    cmdline_arguments_list = cmdline_options.getArgumentsList("--path");
    if (cmdline_arguments_list.empty()) {
#ifdef CYGWIN
        const char* p_home = "C:\\";
#else
        const char* p_home = getenv("HOME");
#endif
        if (nullptr == p_home) {
            cerr << "ERROR! --path argument setting wrong! " << endl;
            return(EXIT_FAILURE);
        }
        path = p_home;
    } else {
        path = cmdline_arguments_list[0];
    }
    path += "/SS_certs@";

    Time current_time;
    path += current_time.getMonth(2) + current_time.getDayInMonth(2) +
            current_time.getHour(2) + current_time.getMinute(2) + current_time.getSecond(2);

#ifdef CYGWIN
    // windows path style
    replace(path.begin(), path.end(), '/', '\\');
#endif

    // create dir
    if (-1 == mkdir(path.c_str(), 0755)) {
        cerr << "ERROR! cannot create " << path << ", " << strerror(errno) << endl;
        return(EXIT_FAILURE);
    }

#ifndef CYGWIN
    // convert raw path to standard absolute path. To call realpath() success,
    // path must have created.
    char buffer[PATH_MAX];
    realpath(path.c_str(), buffer);
    path = buffer;
#endif

    cout << "the path to save SS certificate files \"" << RichTxt::bold_on << path << RichTxt::bold_off << "\"; " << endl;
    // <<<<<<<<<<<<<<<<<<
    

    cout << endl;
    cout << "here we go! " << endl;
    cout << endl;

    static const string url_test("http://www.github.com/");
    Itplayer itplayer(mode, url_test, path);
    Efmoe efmoe(mode, url_test, path);
    Boafanx boafanx(mode, url_test, path);

    cout << "bye! " << endl;


    cout << endl;
    return(EXIT_SUCCESS);
}

