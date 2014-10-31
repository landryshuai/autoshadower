// last modified 

#include "Jslink.h"
#include <iostream>
#include <algorithm>
#include "../helper/Misc.h"
#include "../helper/RichTxt.h"

using namespace std;


const string Jslink::jslink_url("http://www.jslink.org/about");

Jslink::Jslink (Certificate::Mode mode, const string& url_test, const string& savas_path)
    : Webpage(jslink_url)
{
    if (!isLoaded()) {
        cerr << "ERROR! " << jslink_url << " loaded failure. " << endl;
        return;
    }
cerr << getTxt() << endl;

    // 解析证书信息
    static const string keyword_cert_begin("margin-top: 20px;\">");
    static const string keyword_cert_end("<hr>");
    const pair<string, size_t> pair_cert = fetchStringBetweenKeywords( getTxt(),
                                                                       keyword_cert_begin,
                                                                       keyword_cert_end );
    string cert_tmp = pair_cert.first;
    
    // 为了增强解析不同免费 SS 帐号网站的通用性，先证书信息中
    // 的双引号、空格等多余字符
    auto iter = remove_if( cert_tmp.begin(), cert_tmp.end(),
                           [] (char ch) {return('"' == ch || ' ' == ch);} );
    const string cert_clean(cert_tmp.begin(), iter);
    
    // 提取证书中可字段
    const pair<string, size_t> pair_server = fetchStringBetweenKeywords(cert_clean, "server:", "\n");
    const pair<string, size_t> pair_serverport = fetchStringBetweenKeywords(cert_clean, "server_port:", "\n");
    const pair<string, size_t> pair_password = fetchStringBetweenKeywords(cert_clean, "password:", "\n");
    const pair<string, size_t> pair_method = fetchStringBetweenKeywords(cert_clean, "method:", "\n");
    
    // 验证证书并保存至文件
    cout << "check certificate " << pair_server.first << endl;
    cout << ">>>>>>>>" << endl;
    Certificate cert_file( mode,
                           url_test,
                           pair_server.first,
                           pair_serverport.first, 
                           pair_password.first,
                           pair_method.first );
    if (cert_file.isAvailable()) {
        cert_file.saveas(savas_path);
        cout << RichTxt::foreground_green;
        cout << "\\(^o^)/. this SS certificate available. now you can issue SS proxy as follow: " << endl
             << "\tsslocal -s \"" << pair_server.first << "\" -p " << pair_serverport.first
             << " -k \"" << pair_password.first << "\" -b \"127.0.0.1\" -l 1080 -m \""
             << pair_method.first << "\" -t 512" << endl;
        cout << RichTxt::reset_all;
    } else {
        cout << RichTxt::foreground_red;
        cout << " ╮(╯▽╰)╭. this SS certificate unavailable. " << endl;
        cout << RichTxt::reset_all;
    }
    cout << "<<<<<<<<" << endl << endl;
}

Jslink::~Jslink ()
{
    ;
}

