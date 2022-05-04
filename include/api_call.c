// #include <stdio.h>
// #include <stdlib.h>
#include <curl/curl.h>

int get_json()
{
    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/forecast?id=2996944&appid=9ea3f3b997074b2151c3a5ff8e0f48ab");

    struct curl_slist *headers = NULL;
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    // CURLcode ret = curl_easy_perform(hnd);

    FILE *fp = fopen("tmp/weather.json", "wb");

    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, fp);
    curl_easy_perform(hnd);
    curl_easy_cleanup(hnd);
    
    fclose(fp);

    return(0);
}
