// last modified 

#include "Efmoe.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../helper/Misc.h"
#include "../helper/RichTxt.h"

using namespace std;


const string Efmoe::efmoe_url("https://service.efmoe.us/thread-index-fid-1-tid-3-page-1.htm");
static const string user_agent("Mozilla/5.0 (X11; Linux i686; rv:30.0) Gecko/20100101 Firefox/30.0");
static const string cookie("bbs_auth=u2jrXLi%25252FbmhbOpTuLWHefhNx5dshw4vfEKY4SIJ5iNIlEkWfGoTTBzwsQGuXtOL%252Bqetl808W61kl6r%252BJ");


static vector<string>
getServerList (void)
{
    vector<string> server_list;


    static const string server_list_url("https://service.efmoe.us/thread-index-fid-1-tid-100.htm");
    static vector<string> empty_vec;
    Webpage server_list_page(server_list_url, "", "", 16, 2, 2, user_agent, cookie);
    if (!server_list_page.isLoaded()) {
        cerr << "ERROR! " << server_list_url << " loaded failure. " << endl;
        return(empty_vec);
    }

    size_t start_pos = 0;
    while (true) {
        static const string keyword_cert_begin("title=\"\"><span style=\"font-size: 12px;\"><strong><span style=\"color: rgb(255, 165, 0);\">");
        static const string keyword_cert_end("</span>");
        const pair<string, size_t> pair_cert = fetchStringBetweenKeywords( server_list_page.getTxt(),
                                                                           keyword_cert_begin,
                                                                           keyword_cert_end,
                                                                           start_pos );
        const string& server = pair_cert.first;
        if (server.empty()) {
            break;
        }
        start_pos = pair_cert.second;
        
        server_list.push_back(server);
    }


    return(server_list);
}

Efmoe::Efmoe (Certificate::Mode mode, const string& url_test, const string& savas_path)
    : Webpage(efmoe_url, "", "", 16, 2, 2, user_agent, cookie)
{
    if (!isLoaded()) {
        cerr << "ERROR! " << efmoe_url << " loaded failure. " << endl;
        return;
    }

    // 解析证书信息
    static const string keyword_cert_begin("<strong>Shadowsocks</strong>");
    static const string keyword_cert_end("[/hide]</span>");
    const pair<string, size_t> pair_cert = fetchStringBetweenKeywords( getTxt(),
                                                                       keyword_cert_begin,
                                                                       keyword_cert_end );
    const string cert_str = pair_cert.first;
    
    // 提取证书中可字段
    const pair<string, size_t> pair_serverport = fetchStringBetweenKeywords( cert_str,
                                                                             "Server Port：<span style=\"color: rgb(255, 0, 0); \">",
                                                                             "</span>" );
    const pair<string, size_t> pair_password = fetchStringBetweenKeywords( cert_str,
                                                                           "Password：<span style=\"color: rgb(255, 0, 0); \"><strong>",
                                                                           "</strong>" );
    const pair<string, size_t> pair_method = fetchStringBetweenKeywords( cert_str,
                                                                         "Encryption Method：<span style=\"color: rgb(255, 0, 0); \">",
                                                                         "</span>" );
    
    // 获取所有免费服务器名列表
    const vector<string>& server_list = getServerList();

    // 验证证书并保存至文件
    for (const auto& e : server_list) {
        cout << "check certificate " << e << endl;
        cout << ">>>>>>>>" << endl;
        Certificate cert_file( mode,
                url_test,
                e,
                pair_serverport.first, 
                pair_password.first,
                pair_method.first );
        if (cert_file.isAvailable()) {
            cert_file.saveas(savas_path);
            cout << RichTxt::foreground_green;
            cout << RichTxt::bold_on << "\\(^o^)/" << RichTxt::bold_off
                 << ". this SS certificate available. now you can issue SS proxy as follow: " << endl
                 << "\tsslocal -s \"" << e << "\" -p " << pair_serverport.first
                 << " -k \"" << pair_password.first << "\" -b \"127.0.0.1\" -l 1080 -m \""
                 << pair_method.first << "\" -t 512" << endl;
            cout << RichTxt::reset_all;
        } else {
            cout << RichTxt::foreground_red;
            cout << RichTxt::bold_on << " ╮(╯▽╰)╭" << RichTxt::bold_off
                 << ". this SS certificate unavailable. " << endl;
            cout << RichTxt::reset_all;
        }
        cout << "<<<<<<<<" << endl << endl;
    }
}

Efmoe::~Efmoe ()
{
    ;
}

