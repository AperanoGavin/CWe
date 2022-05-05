// #include <stdio.h>
#include <json-c/json.h>
#include "db_connect.c"

int json_parse(){
    FILE *fp;
    char buffer[40000];

    struct json_object *parsed_json;
    struct json_object *tmp;
    struct json_object *lists;
    struct json_object *list;
    struct json_object *main_list;
    struct json_object *temp;
    struct json_object *feels_like;
    struct json_object *temp_min;
    struct json_object *temp_max;
    struct json_object *pressure;
    struct json_object *sea_level;
    struct json_object *grnd_level;
    struct json_object *humidity;
    struct json_object *temp_kf;
    struct json_object *weathers;
    struct json_object *weather;
    struct json_object *main_desc;
    struct json_object *description;
    struct json_object *winds;
    struct json_object *wind_speed, *wind_deg, *wind_gust;
    struct json_object *visibility, *dt_txt;
    struct json_object *city, *name, *sunrise, *sunset;

    char *array[19]={"temp", "feels_like", "temp_min", "temp_max", "pressure", "sea_level", "grnd_level",\
    "humidity", "temp_kf", "main", "description", "wind_speed", "wind_deg", "wind_gust", "visibility", "dt_txt",\
    "name", "sunrise", "sunset"};
    char *json_string[19];

    size_t n_lists, n_weathers, i;

    fp = fopen("tmp/weather.json", "r");
    fread(buffer, 40000, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "list", &lists);
    //printf("list : %s\n", json_object_get_string(lists));
    n_lists = json_object_array_length(lists);
    printf("list length : %ld\n", n_lists);
    for (i = 0; i < 1; i++)
    {
        list = json_object_array_get_idx(lists, i);
        //printf("list : %s\n", json_object_get_string(list));
        tmp = json_object_get(list);
        json_object_object_get_ex(tmp, "main", &main_list);
        tmp = json_object_get(main_list);
        json_object_object_get_ex(tmp, array[0], &temp);
        json_object_object_get_ex(tmp, array[1], &feels_like);
        json_object_object_get_ex(tmp, array[2], &temp_min);
        json_object_object_get_ex(tmp, array[3], &temp_max);
        json_object_object_get_ex(tmp, array[4], &pressure);
        json_object_object_get_ex(tmp, array[5], &sea_level);
        json_object_object_get_ex(tmp, array[6], &grnd_level);
        json_object_object_get_ex(tmp, array[7], &humidity);
        json_object_object_get_ex(tmp, array[8], &temp_kf);

        json_string[0] = (char *)json_object_get_string(temp);
        json_string[1] = (char *)json_object_get_string(feels_like);
        json_string[2] = (char *)json_object_get_string(temp_min);
        json_string[3] = (char *)json_object_get_string(temp_max);
        json_string[4] = (char *)json_object_get_string(pressure);
        json_string[5] = (char *)json_object_get_string(sea_level);
        json_string[6] = (char *)json_object_get_string(grnd_level);
        json_string[7] = (char *)json_object_get_string(humidity);
        json_string[8] = (char *)json_object_get_string(temp_kf);
    }

    tmp = json_object_get(list);
    json_object_object_get_ex(tmp, "weather", &weathers);
    n_weathers = json_object_array_length(weathers);
    //printf("weather length : %ld\n", n_weathers);

    for (i = 0; i < n_weathers; i++)
    {
        weather = json_object_array_get_idx(weathers, i);
        //printf("list : %s\n", json_object_get_string(list));
        tmp = json_object_get(weather);
        json_object_object_get_ex(tmp, array[9], &main_desc);
        json_object_object_get_ex(tmp, array[10], &description);

        json_string[9] = (char *)json_object_get_string(main_desc);
        json_string[10] = (char *)json_object_get_string(description);
    }

    tmp = json_object_get(list);
    json_object_object_get_ex(tmp, "wind", &winds);
    json_object_object_get_ex(winds, "speed", &wind_speed);
    json_object_object_get_ex(winds, "deg", &wind_deg);
    json_object_object_get_ex(winds, "gust", &wind_gust);

    json_string[11] = (char *)json_object_get_string(wind_speed);
    json_string[12] = (char *)json_object_get_string(wind_deg);
    json_string[13] = (char *)json_object_get_string(wind_gust);

    json_object_object_get_ex(tmp, "visibility", &visibility);
    json_string[14] = (char *)json_object_get_string(visibility);

    json_object_object_get_ex(tmp, "dt_txt", &dt_txt);
    json_string[15] = (char *)json_object_get_string(dt_txt);

    json_object_object_get_ex(parsed_json, "city", &city);
    // json_object_object_get_ex(city, "name", &name);
    json_object_object_get_ex(city, "sunrise", &sunrise);
    json_object_object_get_ex(city, "sunset", &sunset);

    // json_string[16] = (char *)json_object_get_string(name);
    json_string[17] = (char *)json_object_get_string(sunrise);
    json_string[18] = (char *)json_object_get_string(sunset);

    printf("Parsed Infos :\n");
    for (i = 0; i < sizeof(json_string)/sizeof(json_string[0]) ; i++)
    {
        printf("%s : %s\n", array[i], json_string[i]);
    }
    printf("Sending to database...\n");
    go_weather(json_string);

    return(0);
}