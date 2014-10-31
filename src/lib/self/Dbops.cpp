// last modified 

#include "Dbops.h"
#include <iostream>
#include <algorithm>
#include "../helper/Misc.h"
#include "../helper/RichTxt.h"

using namespace std;


const string Dbops::dbops_url("http://water.dbops.org/?page_id=15");

Dbops::Dbops (Certificate::Mode mode, const string& url_test, const string& savas_path)
    : Webpage(dbops_url)
{
    if (!isLoaded()) {
        cerr << "ERROR! " << dbops_url << " loaded failure. " << endl;
        return;
    }

    size_t start_pos = 0;
    while (true) {
        // 解析证书信息
        static const string keyword_cert_begin("{<br />");
        static const string keyword_cert_end("}<");
        const pair<string, size_t> pair_cert = fetchStringBetweenKeywords( getTxt(),
                                                                          keyword_cert_begin,
                                                                          keyword_cert_end,
                                                                          start_pos );
        const string cert = pair_cert.first;
        if (cert.empty()) {
            break;
        }
        start_pos = pair_cert.second;
        
        // 提取证书中可字段
        const pair<string, size_t> pair_server = fetchStringBetweenKeywords(cert, "\"Server IP\":\"", "\",<br />");
        const pair<string, size_t> pair_serverport = fetchStringBetweenKeywords(cert, "\"Server port\":", ",</p>");
        const string password_url = fetchStringBetweenKeywords(cert, "<p>\"Password:\"<a href=\"", "\"><strong>").first;
        const string password = Webpage(password_url).getTxt();
        const pair<string, size_t> pair_method = fetchStringBetweenKeywords(cert, "\"Encryption Method\":\"", "\"<br />");
        
        // 验证证书并保存至文件
        cout << "check certificate " << pair_server.first << endl;
        cout << ">>>>>>>>" << endl;
        Certificate cert_file( mode,
                               url_test,
                               pair_server.first,
                               pair_serverport.first, 
                               password,
                               pair_method.first );
        if (cert_file.isAvailable()) {
            cert_file.saveas(savas_path);
            cout << RichTxt::foreground_green;
            cout << "\\(^o^)/. this SS certificate available. now you can issue SS proxy as follow: " << endl
                 << "\tsslocal -s \"" << pair_server.first << "\" -p " << pair_serverport.first
                 << " -k \"" << password << "\" -b \"127.0.0.1\" -l 1080 -m \""
                 << pair_method.first << "\" -t 512" << endl;
            cout << RichTxt::reset_all;
        } else {
            cout << RichTxt::foreground_red;
            cout << " ╮(╯▽╰)╭. this SS certificate unavailable. " << endl;
            cout << RichTxt::reset_all;
        }
        cout << "<<<<<<<<" << endl << endl;
    }
}

Dbops::~Dbops ()
{
    ;
}

